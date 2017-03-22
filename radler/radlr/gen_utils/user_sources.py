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

Created on Dec, 2014

@author: Léonard Gérard leonard.gerard@sri.com
'''
from pathlib import Path

from radler import instrumentation
from radler.astutils.tools import listjoin
from radler.radlr import wd, infos
from radler.radlr.errors import internal_error, error
from radler.radlr.gen_utils import qn


user_src_path = Path('user_src')

find_lib_template = (
"""
SET(CMAKE_MODULE_PATH ${{CMAKE_CURRENT_LIST_DIR}} {})
find_package({} REQUIRED {})
"""
)

def collect_user_files(node_list, src_path=user_src_path):
    """ This function collect the include directories, source files, libraries
    and find library calls to be done to compile the node_list elements.
    """
    include_dirs = []
    source_files = []
    lib_deps = []
    find_libs = []
    for node in node_list:
        for f in node['FILENAME']:
            source_files.append(src_path / wd.of(node) / f._val)
        include_dirs.append(src_path / wd.of(node))
        for l in node['LIB']:
            if l._kind == 'static_library':
                lib_deps.append(qn.cmake_userlib(l))
            elif l._kind == 'cmake_library':
                #RMQ: here we have to do all this mess because add_library(INTERFACE) exists only for cmake v3 not cmake v2...
                # Otherwise, we would not differentiate the library kinds. It would simply be a matter of wrapping things nicely into a library target, see packagen.py. 
                n = l['CMAKE_MODULE']._val
                p = src_path / wd.of(l)
                components = listjoin(' ', (c._val for c in l['CMAKE_COMPONENTS']))
                if l['CMAKE_VAR_LIBRARIES']:
                    lib_deps.append("${{{}}}".format(l['CMAKE_VAR_LIBRARIES']._val))
                else:
                    lib_deps.append("${{{}_LIBRARIES}}".format(n))
                if l['CMAKE_VAR_INCLUDE_DIRS']:
                    include_dirs.append("${{{}}}".format(l['CMAKE_VAR_INCLUDE_DIRS']._val))
                else:
                    include_dirs.append("${{{}_INCLUDE_DIRS}}".format(n))


                find_libs.append(find_lib_template.format(p, n, components))
            else:
                internal_error("unsupported library kind.")
    return source_files, include_dirs, lib_deps, find_libs



def node_sources_type(node):
    """ Return the kind of source of node ('C' or 'CXX'). """
    is_cxx = node['CXX'] != None
    is_c = node['C'] != None
    if is_cxx:
        if is_c:
            error("A node can't have a C and a CXX field.", node._location)
        return 'CXX'
    elif is_c:
        return 'C'
    else:
        error("A node is required to have a C or CXX field.")

def source_node(node):
    """ Return the source field ('C' or 'CXX') of node. """
    return node[node_sources_type(node)]

def gather_user_files(nl, p=user_src_path):
    """ This function calls collect_user_files but then join the resulting lists
    to make it ready as cmake arguments.
    """
    return (listjoin(' ', l, ' ') for l in collect_user_files(nl, p))

def gather_user_file(node, src_path=user_src_path):
    """ Identical to gather_user_files but applies to only one node. """
    return gather_user_files((node,), src_path)

def gather_node_user_file(node, src_path=user_src_path):
    """ Identical to gather_user_files but applies to only one node. """
    return gather_user_file(source_node(node), src_path)

def node_user_header_file(node, src_path=user_src_path):
    """ Header files are not prepended with the user_path
    because the include dir used should take car of that.
    """
    return source_node(node)['HEADER']._val


def gather_user_header_paths(node, src_path=user_src_path):
    """ This function gather the HEADER_PATHS and make them ready for cmake. """
    hps = (src_path / wd.of(node) / p._val for p in node['HEADER_PATHS'])
    return listjoin(' ', hps, ' ')



def user_node_class(node, state_var, in_var, in_f_var, out_var, out_f_var):
    """ The node is searched for a C or CXX class defining the step machine.
    This returns the instructions to initialize the state_var, the
    expression call to do a step and the instructions to finalize the state_var.
    """
    source_type = node_sources_type(node)
    source = node[source_type]
    if source_type == 'C':
        state = source['TYPENAME']
        state = state._val if state else 'RADL_STATE'
        init_fun = source['INIT_FUNCTION']
        init_fun = init_fun._val if init_fun else 'RADL_INIT_FUN'
        step_fun = source['STEP_FUNCTION']
        step_fun = step_fun._val if step_fun else 'RADL_STEP_FUN'
        finish_fun = source['FINISH_FUNCTION']
        finish_fun = finish_fun._val if finish_fun else 'RADL_FINISH_FUN'

        init = "  {t} {v};\n  {i}(&{v});\n".format(
                                            t=state, v=state_var, i=init_fun)
        step = "    {s}(&{v}, {i}, {i_f}, {o}, {o_f});\n".format(
                    s = step_fun, v = state_var,
                    i = in_var, i_f = in_f_var,
                    o = out_var, o_f = out_f_var)
        finish = "  {f}(&{v});\n".format(v=state_var, f=finish_fun)
    elif source_type == 'CXX':
        step_method = source['STEP_METHOD']
        step_method = step_method._val if step_method else 'step'

        init = "  {t} {v};\n".format(t=source['CLASS']._val, v=state_var)
        step = "    {v}.{s}({i}, {i_f}, {o}, {o_f});\n".format(
                    s = step_method, v = state_var,
                    i = in_var, i_f = in_f_var,
                    o = out_var, o_f = out_f_var)
        finish = ""
    else:
        internal_error("Node with unknown source type.\n"+str(node._location))

    if infos.instrument_step_timings:
        step = ( instrumentation.step_timings.print_entering(node._qname)
                + step
                + instrumentation.step_timings.print_exiting(node._qname))
    step = '    // Calling the step function\n' + step
    return init, step, finish
