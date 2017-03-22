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
'''

from radler.radlr.rast import AstVisitor, Ident, Alias

def _un_onleaf(visitor, leaf, namespace):
    """ Make sure Alias leaf are target for their name. """
    if isinstance(leaf, Alias):
        namespace.refresh(leaf._qname, leaf)

def _un_onnode(visitor, node, namespace):
    """ Make sure nodes are target for their name
    and Keep track of the namespace.
    """
    namespace.refresh(node._qname, node)
    visitor.bf(node._children, node._namespace)

# Make sure namespace has correct name->node associations.
updater_ns = AstVisitor(default=_un_onnode, onleaf=_un_onleaf, kind='bf')


def _ui_onleaf(visitor, leaf, namespace):
    """ Correct Ident->node and Alias->node associations. """
    if isinstance(leaf, Ident):
        leaf._reattach(namespace.lookup_node(leaf._qname))
    if isinstance(leaf, Alias):
        ident = leaf._is_alias_of
        ident._reattach(namespace.lookup_node(ident._qname))

def _ui_onnode(visitor, node, namespace):
    """ Keep track of the namespace for faster lookups. """
    visitor.bf(node._children, node._namespace)

# Make sure Idents and Alias are correctly associated.
updater_idents = AstVisitor(default=_ui_onnode, onleaf=_ui_onleaf, kind='bf')


def update_idents(ast, namespace):
    #Before updating the idents, we need to update the namespace
    updater_ns.visit(ast, namespace)
    updater_idents.visit(ast, namespace)
    return ast
