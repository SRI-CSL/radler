# This file is part of Radler.
#
# Radler is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Radler is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Radler.  If not, see <http://www.gnu.org/licenses/>.

'''
@license: GPLv3

Created on Apr 2014

@author: léonard Gérard leonard.gerard@sri.com

The semantics is a function (a parser) defined by the given language
description following the meta grammar.
The program parameter given when called (__call__) is written in this
language.
The output is composed of
    - 'types': a mapping between type names and 
'''

from collections import OrderedDict
from functools import partial

from parsimonious.exceptions import ParseError
from parsimonious.grammar import Grammar
from radler.astutils.location import Location
from radler.astutils.names import NonExistingIdent, ExistingIdent
from radler.astutils.nodeutils import clean_node, ParseVisitor, spprint_node
from radler.astutils.tools import BucketDict, str
from radler.radlr import sanitize, language, infos
from radler.radlr.errors import log4, error, internal_error
from radler.radlr.metaParser import meta_parser
from radler.radlr.rast import AstNode, AstVisitor, Ident
import parsimonious


def loc_of_parsimonious(parsimonious_node):
    return Location(str(infos.source_file), parsimonious_node.full_text,
                        parsimonious_node.start,
                        parsimonious_node.end)

def gen_grammar(language_tree, env):
    # We can update in place kinds, since we do a depth first...
    # not pretty but python dict are easier as mutable variables

    def _unalias(visitor, node, env):
        """ unalias : replace a node with its only child
        """
        (node, env) = visitor.mapred(node, env)
        return node.children[0], env

    symbol = _unalias
    kind = _unalias

    def regex(visitor, node, env):
        """ Keep it as is.
        """
        return node.text, env

    def quoted(visitor, node, env):
        """ A quoted node is a leaf.
        It stores its content in the second child of its choice child.
        """
        return node.children[0][1], env

    def defKind(visitor, node, env):
        """ Verify that the kind is not already defined.
        Return the kind string. The enclosing node has to register k.
        A defKind node has on child the leaf basic_word
        """
        k = node.children[0]
        if k in env.metakinds:
            visitor.error("The kind {k} is already defined.".format(k=k))
        return k, env

    def typ(visitor, node, env):
        """ define a kind and construct the grammar.
        A typ node has six childs 'type' defKind 'REGEX' regex
        """
        (node, env) = visitor.mapred(node, env) #depth first
        (_, kind, _, reg) = node.children
        env.metakinds[kind] = 'type' #register this type
        env.keywords.add(kind) #add the type name to the keywords
        g = """{kind} = {kind}_def / _solo_ident
    {kind}_def = {kind}_not_annoted / {kind}_annoted / _alias_def
    {kind}_annoted = (_ident _ ':' _)? '{kind}' _ {kind}_value
    {kind}_not_annoted = (_ident _)? _ {kind}_value
    {kind}_value = {reg} _
            """.format(**locals())
        return g, env


    def some_kind(visitor, node, env):
        """ two childs kind ('/' kind)*
        """
        (node, env) = visitor.mapred(node, env) #depth first
        (k, o) = node.children
        if o:
            kinds = [k]
            for x in o:
                kinds.append(x[1]) #get the other kinds
            g = '({l})'.format(l=' / '.join(kinds))
        else:
            g = k
        return g, env

    def field(visitor, node, env):
        """
        A field node has three childs symbol some_kind ('*' / '+' / '?')?
        Return the grammar string to match it:
        'symbol kind'
        """
        (node, env) = visitor.mapred(node, env) #depth first
        (name, kind, mod) = node.children
        mod = '+' if mod else ''
        g = "'{name}' _ {kind}{mod}".format(name=name, kind=kind, mod=mod)
        env.keywords.add(name) #register the field name as keyword
        return g, env

    def clas(visitor, node, env):
        """ define a kind and construct the grammar.
        A clas node has three childs 'class' defKind field*
        """
        (node, env) = visitor.mapred(node, env) #depth first
        kind = node.children[1]
        env.metakinds[kind] = 'class' #register this class
        gfield_list = node.children[2]
        fields = "( {0} )".format(') / ('.join(gfield_list))
        g = """{kind} = {kind}_def / _solo_ident
    {kind}_def = {kind}_not_annoted / {kind}_annoted / _alias_def
    {kind}_annoted = (_ident _ ':' _)? '{kind}' _ {kind}_value
    {kind}_not_annoted = (_ident _)? _ {kind}_value
    {kind}_value = '{{' _ ({fields})* '}}' _
            """.format(**locals())
        return g, env

    def meta(visitor, node, env):
        """Concatenate the grammar strings and add the external definitions
        A meta node has only one real child (clas/type)*
        """
        (node, env) = visitor.mapred(node, env) #depth first
        keywords = '|'.join(env.keywords)
        rules = '\n'.join(node.children[0])
        g = r"""{rules}
            _ident = ~r"(?!({keywords})\b)(?!{forbidden_prefix})[a-zA-Z][a-zA-Z0-9_]*"
            _qname = ~r"(?!({keywords})\b)[a-zA-Z][a-zA-Z0-9_.]*"
            _solo_ident = _qname _ !(':' / '{{' / '=')
            _alias_def = _ident _ '=' _ _solo_ident
            _ = ~r"\s*(#[^\r\n]*\s*)*\s*"
            _end = ~r"$"
            """.format(rules=rules, keywords=keywords,
                       forbidden_prefix=env.forbidden_prefix)
        return g, env

    gen = ParseVisitor(locals())
    g, env = gen.visit(language_tree, env)
    if env.metakinds:
        topleveldefs = '_def / '.join(env.metakinds) + '_def'
    else:
        topleveldefs = ''
    lang = """_lang = _ ({tops})* _ _end""".format(tops=topleveldefs)
    log4(lambda:g+lang)
    return Grammar(g+lang, '_lang'), env

def gen_tree_to_ast(language_tree, env):
    #We create a visitor with a visitor... so the convention here is that
    #mvisitor is the meta visitor which is using menv as accumulator, while
    #visitor is the generated one using ast as accumulator.
    #menv is a dictionnary storing the generated visitor methods.

    def typ(mvisitor, mnode, menv):
        """ A typ node has six childs
            'type' defKind 'REGEX' regex
        It generates one rule named kind from defkind
        """
        #No need to do recursive traversal (no rules are generated lower),
        #    but go fetch the kind in defKind.
        kind = mnode.children[1].children[0]

        def m_def_gen(annoted):
            def m_def(visitor, node, namespace):
                childs, _ = visitor.mapacc(node.children, namespace)
                loc = loc_of_parsimonious(node)
                ident = childs[0][0] if childs[0] else None
                if isinstance(ident, parsimonious.nodes.Node):
                    try:
                        qname = namespace.qualify(ident.text)
                    except ExistingIdent:
                        error("This name is already used.", loc)
                else:
                    qname = namespace.generate("_"+kind)
                match_dct = childs[2 if annoted else 1].match.groupdict()
                value = match_dct['value'] if 'value' in match_dct else ''
                if 'unit' in match_dct:
                    normalize = language.unit_normalize[kind][match_dct['unit']]
                    value = normalize(value)
                n = AstNode(kind, qname, [value], namespace, loc)
                namespace.associate(qname, n)
                return n, namespace
            return m_def

        #basic rules are simply replaced by their lone child
        menv[kind] = ParseVisitor.left_mapacc
        menv[kind+'_def'] = ParseVisitor.left_mapacc
        menv[kind+'_value'] = ParseVisitor.left_mapacc
        menv[kind+'_annoted'] = m_def_gen(True)
        menv[kind+'_not_annoted'] = m_def_gen(False)
        return (), menv

    def field(mvisitor, mnode, menv):
        """ A field node has three childs symbol some_kind ('*' / '+' / '?')?
        Return the tuple (symbol, mod)
        """
        (name, _, mod) = mnode.children
        return (name, mod), env

    def clas(mvisitor, mnode, menv):
        """ A clas node has three childs 'class' defKind field*
        Three rules needs to be dealt with, kind, name_def, name_annoted
        with kind the defKind kind.
        """
#         mnode, menv = mvisitor.node_mapacc(mnode, menv)
        kind = mnode.children[1].children[0]
        field_specs = []
        for field in mnode.children[2]:
            mod = field.children[2]
            fname = field.children[0].text
            field_specs.append((fname, mod))

        def m_def_gen(annoted):
            def m_def(visitor, node, namespace):
                ident = node.children[0][0] if node.children[0] else None
                loc = loc_of_parsimonious(node)
                if isinstance(ident, parsimonious.nodes.Node):
                    try:
                        qname = namespace.qualify(ident.text)
                    except ExistingIdent:
                        error("This name is already used.", loc)
                else: #generate a name since none is given
                    qname = namespace.generate("_"+kind)
                thisnamespace = namespace.push(qname)
                childs, _ = visitor.mapacc(node.children, thisnamespace)
                fields = BucketDict(childs[2 if annoted else 1])
                for (fname, mod) in field_specs:
                    v = fields.get(fname, False)
                    err = lambda m: error(m.format(fname), loc)
                    if not mod:
                        if v is False:
                            err("field {} is mandatory.")
                        elif isinstance(v, list):
                            err("field {} requires one and only one value.")
                    elif mod == '?':
                        if v is False:
                            fields[fname] = None
                        elif len(v) != 1:
                            err("field {} may be given at most one value.")
                        else:
                            fields[fname] = v[0]
                    elif mod == '*':
                        if v is False:
                            fields[fname] = []
                    elif mod == '+':
                        if v is False:
                            err("field {} requires at least one value.")
                    else:
                        internal_error("unknown modifier")
                n = AstNode(kind, qname, fields, thisnamespace, loc)
                namespace.associate(qname, n)
                return n, namespace
            return m_def

        #basic rules are simply replaced by their lone child
        menv[kind] = ParseVisitor.left_mapacc
        menv[kind+'_def'] = ParseVisitor.left_mapacc
        menv[kind+'_value'] = partial(ParseVisitor.left_mapacc, el_num=1)
        menv[kind+'_annoted'] = m_def_gen(True)
        menv[kind+'_not_annoted'] = m_def_gen(False)
        return (), menv

    def meta(mvisitor, mnode, menv):
        _ = mvisitor.mapacc(mnode.children, menv)

        def _lang(visitor, node, namespace):
            #depth first, get a list of definitions
            defs, _ = ParseVisitor.left_mapacc(visitor, node, namespace)
            return (loc_of_parsimonious(node), defs), namespace

        def _alias_def(visitor, node, namespace):
            #depth first, return three childs, ident '=' ident
            loc = loc_of_parsimonious(node)
            ((alias, _, target), _) = visitor.mapacc(node.children, namespace)
            try:
                qname = namespace.qualify(alias.text)
            except ExistingIdent:
                error("This name is already used.", loc)
            n = AstNode('_alias', qname, [target], namespace, loc)
            namespace.associate(qname, n)
            return n, namespace

        #get the _ident from _solo_ident
        menv['_solo_ident'] = ParseVisitor.left_mapacc
        menv['_lang'] = _lang
        menv['_alias_def'] = _alias_def
        gen = ParseVisitor(menv)
        return gen, menv

    # generate the visitor and return it.
    metagen = ParseVisitor(locals())
    menv = dict()
    gen, menv = metagen.visit(language_tree, menv)

    # Resolve idents.
    # We are working on an ast with some leafs being parse nodes (_ident).
    def onleaf(visitor, leaf, namespace):
        if isinstance(leaf, parsimonious.nodes.Node):
            if leaf.expr_name != '_qname':
                internal_error("The Ast have parsing node "
                               "{} left over".format(leaf.expr_name))
            try:
                node = namespace.resolve(leaf.text)
            except NonExistingIdent:
                msg = "Undefined identifier {}".format(leaf.text)
                error(msg, loc_of_parsimonious(leaf))
            return Ident(node, loc_of_parsimonious(leaf)), namespace
        else:
            return leaf, namespace
    def onnode(visitor, node, namespace):
        node, _ = visitor.node_mapacc(node, node._namespace)
        return node, namespace
    resolver = AstVisitor(onleaf=onleaf, default=onnode)

    def tree_to_ast(program_tree, program_qname, namespace):
        thisnamespace = namespace.push(program_qname)
        (location, defs), _ = gen.visit(program_tree, thisnamespace)
        ast = AstNode('_ast', program_qname, defs, thisnamespace, location)
        namespace.associate(program_qname, ast)
        ast, _ = resolver.visit(ast, namespace)
        return ast
    return tree_to_ast



class TypingError(Exception):
    def __init__(self, expected, actual):
        self.expected = expected
        self.actual = actual
    def __str__(self):
        return "expected a {e}, but got a {a}".format(e=str(self.expected),
                                                      a=str(self.actual))


def gen_kind_dicts(language_tree):
    """
    The kind_dicts is a dictionary mapping each class name
    to a dictionary of its fields mapping to the possible types.
    """
    kind_dicts = dict()

    def some_kind(mnode):
        """ two childs kind ('/' kind)*
        """
        (k, o) = mnode.children
        r = [k.text]
        for ok in o:
            r.append(ok[1].text)
        return r

    def field(mnode, subdict):
        """
        A field mnode has three childs symbol some_kind ('*' / '+' / '?')?
        """
        (name, kinds, _) = mnode.children
        subdict[name.text] = some_kind(kinds)

    def clas(mvisitor, mnode, menv):
        """
        A clas mnode has three childs 'class' defKind field*
        """
        kind = mnode.children[1].text
        field_dict = dict()
        kind_dicts[kind] = field_dict
        for f in mnode.children[2]:
            field(f, field_dict)

    ParseVisitor({'clas': clas}, kind='bf').visit(language_tree, ())
    return kind_dicts



class Semantics:
    """Once initialized the semantics has five main attributes,
    -metakinds maps kind_name -> 'class' | 'type'
    -keywords is a set of keywords
    -forbidden_prefix is a reserved prefix
    -lang_version the language version
    -grammar is the parsimonious grammar
    Moreover, the initialization bootsrap the parser and checker.
    """
    def __init__(self, language):
        self.metakinds = OrderedDict()
        self.keywords = set(language.extra_keywords)
        self.forbidden_prefix = getattr(language, 'forbidden_prefix', '')
        self.lang_version = language.version
        language_tree = meta_parser(language.defs)
        self.grammar, _ = gen_grammar(language_tree, self)
        self.tree_to_ast = gen_tree_to_ast(language_tree, self)
        self.kind_dicts = gen_kind_dicts(language_tree)

    def __call__(self, program, program_qname, root_namespace):
        """ The parser """
        try:
            program_tree = self.grammar.parse(program)
            program_tree = clean_node(program_tree, to_prune=['_', '_end'],
                                      keep_regex=True)
        except ParseError as e:
            loc = Location('', e.text, e.pos, e.pos+1)
            msg = ("Could not match rule named '{r}' defined by\n{rhs}"
                   "".format(r=e.expr.name, rhs=e.expr._as_rhs()))
            error(msg, loc)
        log4(lambda: spprint_node(program_tree))
        ast = self.tree_to_ast(program_tree, program_qname, root_namespace)
        ast = sanitize.update_idents(ast, root_namespace)
        log4(lambda: str(ast))
        return ast


