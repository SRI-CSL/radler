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

Created on Jun, 2014

@author: Léonard Gérard leonard.gerard@sri.com

In RADL, types are structural.

TODO: 6 for now we assume types not to be recursive.
'''
from collections import namedtuple
import re

from radler.radlr import infos, language
from radler.radlr.errors import error, internal_error
from radler.radlr.rast import AstVisitor, flatten_children, Ident, Alias


class ArrayType(namedtuple('array_type', ['size', 'elem_t'])):
    """ An array type has two fields, size and elem_t.
    """
    def __str__(self):
        return "{}[{}]".format(str(self.elem_t), self.size)

class StructType(namedtuple('struct_type', ['shallow', 'elems_t'])):
    """elems_t should be a tuple of tuples (field_name, field_type).
    The type is canonical since field_name are reordered to be sorted.
    """
    def __new__(cls, shallow, elems_t):
        elems_t = sorted(elems_t, key=(lambda v:v[0]))
        return super().__new__(cls, shallow, tuple(elems_t))

    def __str__(self):
        return "struct {{{}}}".format(', '.join(map(str, self.elems_t)))

class EmptyType:
    def __str__(self):
        return "EmptyType"

def are_eq(t1, t2):
    """Return types equality, structs are structurally compared
    """
    return t1 == t2

sized_type_regex = re.compile(r"(?P<base>[a-zA-Z]+)(?P<size>\d+)")

def is_sub(t1, t2):
    """Returns whether t1 is a subtype of t2.
    """
    if isinstance(t1, ArrayType) and isinstance(t1, ArrayType):
        return (t1.size == t2.size) and is_sub(t1.elem_t, t2.elem_t)
    elif isinstance(t1, StructType) and isinstance(t1, StructType):
        e1l = t1.elems_t
        e2l = t2.elems_t
        if len(e1l) != len(e2l): return False
        for ((f1, ft1), (f2, ft2)) in zip(e1l, e2l):
            # note that fields are sorted by definition of StructType
            if f1 != f2 or not is_sub(ft1, ft2):
                return False
        return True
    elif isinstance(t1, str) and isinstance(t2, str):
        if t1 == t2:
            return True
        r1 = sized_type_regex.match(t1)
        r2 = sized_type_regex.match(t2)
        if not r1 or not r2: #one of them doesn't match the regex
            return False
        (b1, s1), (b2, s2) = r1.groups(), r2.groups()
        return b1 == b2 and b1 in language.sized_types and int(s1) <= int(s2)
    elif isinstance(t1, EmptyType) and isinstance(t2, EmptyType):
        return True
    else:
        return False

def smallest_type(value, t):
    """ Look for the smallest type able to store value.
    Assumes that t is a correct type.
    """
    #TODO: 8 the implementation should do a dichotomic search
    b, s = sized_type_regex.match(t)
    sizes = language.sized_types.get(t, [])
    for cs in sizes: # sizes are expected to be increasing.
        if cs >= s:
            return t
        if language.check_type_size[t](value, cs):
            return b+str(cs)
    return t

def _check_kind(node, expected):
    """ Verify that the kind of node is as expected (a subtype of one of them).
    Returns the first kind from expected fitting node.
    """
    loc = node._location
    actual = node._kind
    #No approximation first
    if actual in expected:
        return actual
    for k in expected:
        if is_sub(actual, k):
            return k
    #Actual is not correct
    if len(expected) == 0:
        internal_error("No expected type.")
    if isinstance(node, Alias):
        msg1 = "This value, resolved to {},".format(node._is_alias_of._qname)
    elif isinstance(node, Ident):
        msg1 = "This value, resolved to {},".format(node._qname)
    else:
        msg1 = "This value"
    if len(expected) == 1:
        error(msg1+" is of type {},\nwhen a value of type {} is expected."
              "".format(actual, expected[0]), loc)
    else:
        error(msg1+" is of type {},\n"
              "when a value of type among the following set is expected\n"
              "{{{}}}".format(actual, ', '.join(expected)), loc)


def _type_term(node, mk, expected):
    """ Compute and check the type of a rast term (node, ident, alias, None).
    If the node was user annotated, do not change the type, only check it.
    """
    if not node:
        pass #checking the type of a phantom node (None is a valid leaf).

    #Check the kind to be expected
    kind = _check_kind(node, expected)

    #Compute the type
    if mk == 'type':
        # Use the language checkers if it exists.
        check = language.check_type.get(kind, None)
        if check:
            check(node._val, node._location)
        t = kind
    elif mk == 'class' and node._kind == 'array':
        def check_el(el, ex_t):
            elt = of(el)
            if not is_sub(elt, ex_t):
                error("This array element has type {} when {} is expected."
                      "".format(str(elt), str(ex_t)), el._location)
        expected_t = node['TYPE']
        expected_size = node['SIZE']
        values = node['VALUES']
        # check size
        if expected_size and len(values) != int(expected_size._val):
            error("This array is of size {} when {} is expected."
                  "".format(len(values), expected_size._val), node._location)
        # use first element if no expected_elem_t is found
        if not expected_t:
            expected_t = of(values[0])
        else:
            expected_t = expected_t._val
            check_el(values[0], expected_t)
        for el in values[1:]:
            check_el(el, expected_t)
        t = ArrayType(len(values), expected_t)
    elif mk == 'class' and (node._kind in ('struct', 'topic')):
        fields = (((f._name, of(f)) for f in node['FIELDS']))
        t = StructType(False, tuple(fields))
    else:
        """ Generic class of the AST, we are doing type 2 (see ASTdump),
        so we flatten the node and doesn't keep 'False' (None) nodes.
        """
        l = flatten_children(node)
        l_noident = [c for c in l if c and not isinstance(c, Ident)]
        if l_noident:
            t = StructType(True, ((c._name, of(c)) for c in l_noident))
        else:
            t = EmptyType()
    #Store the computed type
    node._type = t



def _is_current_module(node):
    return node._qname.has_root(infos.ast._qname)  # @UndefinedVariable


def typecheck(ast):
    """ Check the type of the ast recursively.
    """
    metakinds = infos.semantics.metakinds  # @UndefinedVariable
    kind_dicts = infos.semantics.kind_dicts  # @UndefinedVariable

    def on_ast_nodes(visitor, node, expected):
        if _is_typed(node):
            return #Already visited, because of force visitation
        mk = metakinds[node._kind]
        if mk == 'class':
            for field in node._children:
                visitor.visit(node[field], kind_dicts[node._kind][field])
        _type_term(node, mk, expected)

    def on_ast_leafs(visitor, leaf, expected):
        if leaf and _is_typed(leaf):
            _check_kind(leaf, expected)
            return #Already typed and visited, because of force visitation
        #### force visitation to enable recursives types...
        if isinstance(leaf, Ident) and _is_current_module(leaf._node): #TODO 5: use follow_modlocal_links
            visitor.visit(leaf._node, expected)
        if isinstance(leaf, Alias):
            target = leaf._is_alias_of
            if _is_current_module(target):
                visitor.visit(target, expected)
        #### end of forcing the recursivity
        if leaf:
            _type_term(leaf, metakinds[leaf._kind], expected)

    checker = AstVisitor(default=on_ast_nodes, onleaf=on_ast_leafs, kind='bf')
    checker.node_bf(ast, list(metakinds))
    _type_term(ast, 'ast', ['_ast'])


def _is_typed(node):
    """ Once a node has been typed, its type is stored in its _type field. """
    return hasattr(node, '_type')


def of(node):
    """Return the type of a node, assumes typecheck has been done.
    """
    if not _is_typed(node):
        if node is None:
            internal_error("asking for type of None")
        internal_error("Typing hasn't been done on the node {}."
                       "".format(node._qname), node._location)
    return node._type
