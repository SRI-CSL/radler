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

Created on Sept, 2014

@author: Léonard Gérard leonard.gerard@sri.com

Utilities to generate C code from an ast or rast nodes.

'''
from radler.radlr import language, infos, types
from radler.radlr.errors import internal_error
from radler.radlr.gen_utils import qn
from radler.radlr.types import StructType, ArrayType, EmptyType


##############
def typedeclof(t):
    """ Return if it exists, the type name associated with the radl type t.
    It will return None in case there is no known type declaration.
    The know declarations are stored in infos.c_typedecl.
    """
    if isinstance(t, str):
        tname = language.type_mapping[t]['C']
        return tname
    else:
        return infos.c_typedecl.get(t, None)

def decl_and_def_type(t, tname, register_type=True):
    """ This function generate the C type declaration and definition of the 
    RADL type t. The typename (typedefed) associated is tname.
    If register_type is True, the type is registered in the global type map
    (infos.c_typedecl) so that the the typename is recoverable from the type.

    It returns tdecl, tdef, decl_deps and def_deps:
    - tdecl is the type declaration, (the typedef), usually to be written in 
    the header file.
    - tdef is the type actual definition. Note that this may be empty,
    for example for array types.
    - decl_deps is an enumeration of other typenames onto which tdecl depends
    - def_deps is a enumeration of other typenames onto which tdef depends.
    """
    if isinstance(t, ArrayType):
        el_t = typedeclof(t.elem_t)
        s = t.size
        tdecl = "typedef {} {}[{}];\n".format(el_t, tname, s)
        decl_deps = (el_t,)
        tdef = ''
        def_deps = ()
    elif isinstance(t, StructType):
        tdecl = "typedef struct {} {};\n".format(tname, tname)
        decl_deps = ()
        tdef = "struct {} {{\n".format(tname)
        def_deps = []
        tdef_template = "  {}* {};\n" if t.shallow else "  {} {};\n"
        for (f_name, f_type) in t.elems_t:
            f_t = typedeclof(f_type)
            def_deps.append(f_t)
            tdef += tdef_template.format(f_t, f_name)
        tdef += '};\n'
    elif isinstance(t, EmptyType):
        tdecl = "typedef int8_t {};\n".format(tname)
        decl_deps = ()
        tdef = ''
        def_deps = ()
    else:
        internal_error("unknown type instance")
    if register_type:
        infos.c_typedecl[t] = tname
    return (tdecl, tdef, decl_deps, def_deps)


def copy_to(var, node, shallow=True, init=False):
    """ Used to copy the value of node in var.
    Require a node with actual access to its values (._val).
    The var is expected to be allocated and of the correct type.
    @param deep: if True the copy will be deep (recursively). If shallow (False)
    it requires cvarname(node) to already be defined so it can be referenced.
    @param init: if True, it assumes that the value of cvarname(node) isn't
    initialized. The init flag is turned off for any internal copy, thus if
    shallow, any internal variable used by node is assumed to be initialized.
    """
    t = types.of(node)
    if shallow and not init:
        yield var + ' = &' + qn.c_varname(node) + ';'
    else: #Deep copy of this level
        if isinstance(t, str): #Basic types, always do deep copy.
            v = language.value_mapping[t]['C'](node._val)
            yield var + ' = ' + v + ';'
        elif isinstance(t, StructType):
            for (f_name, _) in t.elems_t:
                v = getattr(node, f_name)
                yield from copy_to(var+'.' + f_name, v, shallow and t.shallow, False)
        elif isinstance(t, ArrayType):
            vs = node['VALUES']
            for i,v in enumerate(vs):
                yield from copy_to(var+'['+str(i)+']', v, False, False)
        elif isinstance(t, EmptyType):
            yield var + ' = 0;'
        else:
            internal_error("Type unsupported.")
