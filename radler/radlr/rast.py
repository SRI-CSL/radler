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

Created on May, 2014

@author: Léonard Gérard leonard.gerard@sri.com

'''
from collections import Mapping

from radler.astutils.names import NonExistingIdent
from radler.astutils.nodetrees import Functor
from radler.radlr import infos
from radler.radlr.errors import internal_error, noloc


class AlreadyAttached(Exception): pass


class Ident(Mapping):
    """" An ident is a reference to an actual node, it bears the same name
    but has its own location"""
    __slots__ = ['_location', '_node']
    def __init__(self, node, location):
        self._location = location
        self._node = node
    def __getstate__(self):
        """ Allows pickling: necessary because of __getattr__"""
        return tuple(getattr(self, a) for a in Ident.__slots__)
    def __setstate__(self, state):
        """ Allows pickling: necessary because of __getattr__"""
        for a,v in zip(Ident.__slots__, state): setattr(self, a, v)

    @classmethod
    def of(cls, node_or_ident):
        if isinstance(node_or_ident, Ident):
            return Ident(node_or_ident._node, noloc())
        else:
            return Ident(node_or_ident, noloc())

    def _attach(self, node):
        if self._node:
            raise AlreadyAttached()
        self._node = node
    def _reattach(self, node):
        self._node = node

    def __repr__(self):
        return str(self._qname)
    #container convention, behave like node
    def __len__(self):
        return len(self._node)
    def __getitem__(self, key):
        return self._node[key]
    def __iter__(self):
        return iter(self._node)
    def __setattr__(self, attr, value):
        if attr in self.__slots__:
            object.__setattr__(self, attr, value)
        else:
            setattr(self._node, attr, value)
    def __getattr__(self, attr):
        return getattr(self._node, attr)
    def __copy__(self):
        internal_error("Trying to copy an Ident.")
    def __deepcopy__(self, d):
        internal_error("Trying to deepcopy an Ident.")

    def __eq__(self, other):
        return self._qname == getattr(other, '_qname' , None)


_unique_val = object()

class Alias(Mapping):
    """ Note that Alias have their own fields when edited.
    Some reserved fields are _qname, _location, _is_alias_of.
    """
    def __init__(self, qname, location, target_ident):
        self._qname = qname
        self._location = location
        self._is_alias_of = target_ident

    @property
    def _name(self):
        return self._qname.name()

    def __getattr__(self, attr):
        """ Fall back to the node """
        return getattr(self._node, attr)

    def __getstate__(self):
        """ Allows pickling: necessary because of __getattr__"""
        return self.__dict__
    def __setstate__(self, state):
        """ Allows pickling: necessary because of __getattr__"""
        self.__dict__.update(state)

    @property
    def _node(self):
        return self._is_alias_of._node
    #container convention, behave like node
    def __len__(self):
        return len(self._node)
    def __getitem__(self, key):
        return self._node[key]
    def __iter__(self):
        return iter(self._node)
    def __eq__(self, other):
        return self._qname == getattr(other, '_qname' , None)

class AstNode(Mapping):
    """ Basically a named kind with children.
    Inherit its container behavior from its children container.
    """
    def __init__(self, kind, qname, children, namespace, location):
        self._kind = kind
        self._qname = qname
        self._children = children
        self._namespace = namespace
        self._location = location

    @property
    def _name(self):
        return self._qname.name()

    @property
    def _val(self):
        """ Used for nodes holding one value as their unique child."""
        if len(self._children) != 1:
            internal_error("Tried to get _val of a node with {} childs"
                           "".format(len(self._children)))
        return self._children[0]
    #container convention, behave like _children
    def __len__(self):
        return len(self._children)
    def __getitem__(self, key):
        try:
            return self._children[key]
        except (KeyError, TypeError):
            pass #TypeError is useful in case _children is a list and key a str
        pa = list(iter(self._children))
        raise KeyError("{a} is not among the possibilities:"
                       "{pa}".format(a=key, pa=pa))
    def __iter__(self):
        return iter(self._children)
    def __getattr__(self, attr):
        """Attributes are namespace lookup.
        """
        #ensure we have a _namespace attribute in case __getattr__ is called
        #before init (for example when using copy).
        object.__getattribute__(self, '_namespace')
        try:
            return self._namespace[attr]
        except NonExistingIdent: pass
        raise AttributeError(attr)

    @property
    def _typed_name(self):
        return "{n} : {k}".format(n=self._name, k=self._kind)

    def __str__(self):
        return str(self._qname)

    def __repr__(self):
        pass # This is defined after the class definition

    def __eq__(self, other):
        return self._qname == getattr(other, '_qname' , None)

AstNode.__repr__ = Functor(AstNode, '_children', '_typed_name').spprint_node

nodetree_kind = Functor(AstNode, '_children', '_kind')
#The visitor for Ast and AstNodes
AstVisitor = nodetree_kind.Visitor

def follow_links(on_other_leaf):
    def _follow_links(visitor, leaf, acc):
        if isinstance(leaf, Ident):
            return visitor.visit(leaf._node, acc)
        elif isinstance(leaf, Alias):
            return visitor.visit(leaf._is_alias_of, acc)
        else:
            return on_other_leaf(visitor, leaf, acc)
    return _follow_links

def follow_modlocal_links(on_other_leaf):
    def _is_current_module(node):
        return node._qname.has_root(infos.ast._qname)  # @UndefinedVariable
    def _follow_links(visitor, leaf, acc):
        if isinstance(leaf, Ident) and _is_current_module(leaf._node):
            return visitor.visit(leaf._node, acc)
        elif isinstance(leaf, Alias) and _is_current_module(leaf._is_alias_of):
            return visitor.visit(leaf._is_alias_of)
        else:
            return on_other_leaf(visitor, leaf, acc)
    return _follow_links

#getting children of a node (flattened, by passing the containers).
flatten_children = nodetree_kind.flatten_children



