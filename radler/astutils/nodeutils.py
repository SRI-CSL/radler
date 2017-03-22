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

Created on May 2014

@author: Léonard Gérard leonard.gerard@sri.com

'''

from copy import copy

from parsimonious.nodes import Node
from radler.astutils.nodetrees import Functor


nodetreesutils = Functor(Node, 'children', 'expr_name')
ParseVisitor = nodetreesutils.Visitor
spprint_node = nodetreesutils.spprint_node


def prune(node, to_prune=[]):
    """Remove to_prune subnodes in a parsimonious.Node.
        Nodes boundaries are updated according to pruned subnodes.
        If the root is pruned, return None.
    """
    if node.expr_name in to_prune:
        return None
    #Note, the mapred accumulator stores the computed boundaries as a tuple
    def prune(visitor, l, _):
        # Filter first, BEFORE visiting
        # -> which prevents lifting in the same pass.
        def isto_keep(x):
            if not isinstance(x, Node):
                return True
            else:
                return x.expr_name not in to_prune
        l = list(filter(isto_keep, l))
        return visitor.list_mapred(l, _)

    def default(visitor, n, _):
        children, _ = visitor.visit(n.children) #depth first
        node = copy(n)
        node.children = children
        if n.children: # We had children so our width come from them.
            if children:
                node.start = children[0].start
                node.end = children[-1].end
            else: # We lost all children, so we are empty
                node.end = node.start
        else: # We are a leaf kind of node (like __Literal__)
            pass
        return node, _

    node, _ = ParseVisitor(default=default,
                           ontuple=prune, onlist=prune).visit(node)
    return node

def lift(node):
    """lift as follow:
            exp* (ZeroOrMore) becomes a list
            exp+ (OneOrMore) becomes a list
            exp exp (Sequence) becomes a list
            exp / exp (OneOf) is replaced by its only child
    """
    lift = ParseVisitor.lift_mapacc
    lift_the_child = ParseVisitor.left_mapacc
    d = {'__ZeroOrMore__' : lift, '__OneOrMore__' : lift,
         '__Sequence__' : lift, '__OneOf__' : lift_the_child}
    node, _ = ParseVisitor(d).visit(node)
    return node


def eval_leafs(node, txt_leaf=[], keep_regex=False):
    """ any node in txt_leaf is replaced by str of itself,
        'exp' (Literal) becomes the value
        ~regex (Regex) becomes the matched string
        exp? (Optional) becomes None or the value
    """
    def textify(visitor, node, _):
        return node.text, _
    def optional(visitor, node, _):
        children, _ = visitor.visit(node.children) #depth first
        l = len(children)
        if l==0:
            return None, _
        elif l==1:
            return children[0], _
        else:
            visitor.error("Optional leaf with multiple children.")

    d = dict()
    if keep_regex:
        basic_txt_leaf = ['__Literal__']
    else:
        basic_txt_leaf = ['__Literal__', '__Regex__']
    for n in basic_txt_leaf + txt_leaf:
        d[n] = textify
    d['__Optional__'] = optional
    node, _ = ParseVisitor(d).visit(node)
    return node


def clean_node(node, to_prune=[], txt_leaf=[], keep_regex=False):
    """prune, lift and eval leafs
    """
    return eval_leafs(lift(prune(node, to_prune)), txt_leaf, keep_regex)

