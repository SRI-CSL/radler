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

Here we define what is a qualified name.
'''

from collections.abc import MutableMapping

class ExistingIdent(Exception): pass
class NonExistingIdent(KeyError):
    @property
    def ident(self):
        return self.args[0] if self.args[0] else "{not provided}"

class QualifiedName(tuple):
    def __new__(cls, modname, name, generated):
        """Create a qualified name,
        modname should be a Name,
        name a string,
        generated is True if this name is not extracted from the source."""
        return tuple.__new__(cls, (modname, name, generated))
    def __getnewargs__(self):
        """Allows pickling."""
        return self
#     @classmethod
#     def namein(cls, name, generated, namespace):
#         """Create a qualified name using its enclosing namespace."""
#         return cls(namespace.modname(), name, generated)
    def name(self):
        """local name"""
        return self[1]
    def modname(self):
        """enclosing module of this name"""
        return self[0]
    def asmodule(self, sep='/', root=None):
        return self.qname(sep, root) + sep
    def qname(self, sep, root=None, prefix='', suffix=''):
        """Qualified name"""
        return self[0].asmodule(sep, root) + prefix + self[1] + suffix
    def rootmodule(self, childmodule=None):
        """ Return the root module  (for m1.m2.m3.n returns m1). """
        return self[0].rootmodule(self)

    def mangle(self, reserved_prefix, manglespace):
        """ Generate a string unique to this qualname.
        The reserved_prefix should be forbidden in user names.
        The manglespace provides multiple 'namespaces' for one qualname.
        Typical use is 'n' for variable name and 't' for variable type.
        To ensure uniqueness, the manglespace can't contain underscores and
        the reserved_prefix needs to end with one.
        """
        n = self[1]
        nn = str(len(n))
        if manglespace == 'rosmsg': 
            return ''.join(e for e in self[0].mangle(reserved_prefix, manglespace) + '_' + nn + '_' + n if e.isalnum()).title()
        return self[0].mangle(reserved_prefix, manglespace) + '_' + nn + '_' + n
    def generated(self):
        return self[2]
    def pathwalk(self):
        yield from self[0].pathwalk()
        yield self[1]
    def pathwalk_relativeto(self, qname):
        me = self.pathwalk()
        root = qname.pathwalk()
        for n1,n2 in zip(me, root):
            if n1 != n2: return None
        if next(root, False): return None
        else: return me
    def has_root(self, qname):
        """ return whether qname is a root of this qualname.
        For example m1.m2.m3 will have m1 or m1.m2 or m1.m2.m3 as root.
        """
        p = self.pathwalk_relativeto(qname)
        return p != None
    def str_relativeto(self, qname, sep='.'):
        """ return the representation relative to modname.
        If it is not included in modname, print qualified name."""
        p = self.pathwalk_relativeto(qname)
        return sep.join(iter(p)) if p else self.qname(sep)
    def __str__(self):
        return self.qname('.')
    def __len__(self, acc=0):
        return self.modname().__len__(acc+1)


class _RootQName(QualifiedName):
    """Names need a root since they are left recursive.
    This class has an unexpected behavior since the 'global root' is usually
    unnamed and implicit. That is why, its representation is usually ''
    except when some specific root is required (like '/' for filepath),
    in which case the root param needs to be set.
    That is also why its length is 0.
    """
    def __new__(cls): return tuple.__new__(cls,())
    def name(self): return ''
    def modname(self): raise Exception("rootname doesn't have modname")
    def rootmodule(self, childmodule=None):
        if childmodule == None:
            raise Exception("Trying to get root module of empty name.")
        else:
            return childmodule
    def qname(self, sep='', root=None): return root if root else ''
    asmodule = qname
    def mangle(self, reserved_prefix, manglespace):
        return reserved_prefix + manglespace
    def generated(self): return True
    def pathwalk(self): return iter([]) #empty iterator.
    def __len__(self, acc=0): return acc


class Namespace(MutableMapping):
    def __init__(self, qname, father):
        """ A namespace have one father namespace. """
        self.father = father
        self.qname = qname
        self.idents = dict()
        self.gen_last_num = dict()
    @property
    def root(self):
        return self.father.root

    def qualify(self, name):
        """ Book the name in the namespace and return the qualified name.
        @raise ExistingIdent when name is already defined in this namespace.
        """
        try: self[name] #Verify it is not booked
        except KeyError: self[name] = None #Book it
        else: raise ExistingIdent(name)
        return QualifiedName(self.qname, name, False)

    def generate(self, name):
        """ Tries to register a name, if it already exists append a
        fresh number to it.
        """
        #The generation happens a lots with the same name
        try: n = self.gen_last_num[name]
        except KeyError: n = 0
        while True: #Loop until an undefined name is found.
            n = n+1
            iname = "{name}{n}".format(name=name, n=n)
            try:
                self.idents[iname]
            except KeyError:
                self.gen_last_num[name] = n
                self.idents[iname] = None #Book it
                return QualifiedName(self.qname, iname, True)

    def resolve(self, source_qname):
        """ Tries to find the nearest definition of source_qname.
        The source_qname may be partially qualified in which case we resolve
        the root first then lookdown from there.
        """
        qn_l = source_qname.split('.')
        rootnamespace, _ = self._resolve(qn_l[0])
        try:
            return rootnamespace.lookdown_node(iter(qn_l))
        except NonExistingIdent:
            pass # We will populate the actual name
        except Exception as e:
            raise Exception("Unexpected exception while lookup_node {}:\n{}"
                            "".format(source_qname, e))
        raise NonExistingIdent(source_qname)

    def _resolve(self, name):
        """ Tries to qualify a simple name to the nearest definition:
        goes up to the first definition, while checking opened namespaces.
        """
        try:
            return self, self[name]
        except NonExistingIdent: pass
        return self.father._resolve(name) #the root namespace stop the recursion

    def associate(self, qname, node):
        assert(qname.modname() == self.qname)
        self[qname.name()] = node

    def refresh(self, qname, node):
        """ Reassociating name with a new node. """
        assert(qname.modname() == self.qname)
        try: self[qname.name()] #verify it already exists
        except KeyError: raise Exception("Refreshing an unknown ident.")
        self.associate(qname, node)

    def lookup_node(self, qname):
        """ The qname has to be fully qualified.
        If not found, raise NonExistingIdent(name)
        """
        if qname.modname() == self.qname: #shortcut for fast local name lookups
            return self[qname.name()]
        try:
            return self.root.lookdown_node(qname.pathwalk())
        except NonExistingIdent:
            pass # We will populate the actual name
        except Exception as e:
            raise Exception("Unexpected exception while lookup_node {}:\n{}"
                            "".format(qname, e))
        raise NonExistingIdent(qname)

    def lookdown_node(self, path):
        try:
            return self._lookdown_node(next(path), path)
        except (KeyError, AttributeError): pass
        raise NonExistingIdent

    def _lookdown_node(self, name, pathwalkleft):
        nextname = next(pathwalkleft, False)
        if nextname:
            return self[name]._namespace._lookdown_node(nextname, pathwalkleft)
        else:
            return self[name]

    def push(self, qname):
        """ Return a new namespace with self as father.
        Rmq, the father isn't copied, a reference is kept, allowing any later
        modification of the father to be taken into account in its childs. """
        return Namespace(qname, self)

    def pop(self):
        """ Return the father namespace. """
        return self.father

    def __str__(self): return str(self.idents.keys())
    def __repr__(self): return str(self)
    #MutableMapping convention, behave like the idents dict
    def __getitem__(self, name):
        try :
            return self.idents[name]
        except KeyError:
            raise NonExistingIdent(name)
    def __setitem__(self, name, value): self.idents[name] = value
    def __delitem__(self, name): del self.idents[name]
    def __len__(self): return len(self.idents)
    def __iter__(self): return iter(self.idents)
    #No copy
    def __copy__(self): raise Exception("Trying to copy an Ident.")
    def __deepcopy__(self, d): raise Exception("Trying to deepcopy an Ident.")

class RootNamespace(Namespace):
    def __init__(self):
        self.qname = _RootQName()
        self.idents = dict()
        self.gen_last_num = dict()
    def _resolve(self, name):
        return self, self[name]
    @property
    def root(self): return self
    @property
    def father(self): raise Exception("A root namespace has no father.")
    def pop(self): raise Exception("A root namespace can't be popped.")
