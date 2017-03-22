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
from radler.astutils.nodetrees import fun_dict_of
from radler.astutils.tools import write_file, link_path, listjoin
from radler.radlr import infos, wd
from radler.radlr.cgen import ASTdump
from radler.radlr.gen_utils import qn, catkin_pkg
from radler.radlr.gen_utils.user_sources import user_src_path, gather_user_files,\
    gather_user_header_paths, gather_user_file
from radler.radlr.rast import AstVisitor, follow_modlocal_links
from radler.radlr.workspace import ws_path


def app(d, templates):
    for (s,t) in templates.items():
        v = t.format(**d)
        if s not in d or not d[s]:
            d[s] = v
        else:
            d[s] += v

def clear(d, templates):
    for s in templates:
        d[s] = ''


cmake_templates = {
'cmakelists':
"""
cmake_minimum_required(VERSION 2.8.12)

project({package_name})

find_package(catkin REQUIRED {ast_deps})

catkin_package(LIBRARIES {ast} {libs})

add_definitions(-DIN_RADL_GENERATED_CONTEXT)
"""
"{defs}"
"""
{module_find_libs}
add_library({ast} STATIC {ast_c_filename}{module_sources})
target_include_directories({ast} PUBLIC include PRIVATE{module_includes})
target_link_libraries({ast} ${{catkin_LIBRARIES}}{module_libs})
target_compile_definitions({ast}
  PRIVATE RADL_MODULE_NAME={namespace}
  PRIVATE RADL_MODULE={ast_fun}\(\)
  PRIVATE RADL_HEADER="{ast_h_filename}"
)
set_target_properties({ast} PROPERTIES radl_user_src
  ${{CMAKE_CURRENT_LIST_DIR}}/{user_src_folder}
)

"""
}

## user defined lib level
#
# lib_target : the cmake target for this lib

# lib_static_files : the (static) library files
# lib_static_pub_dirs : the (static) library public include directories
# lib_static_priv_dirs : the (static) library private include directories
# lib_static_libs : the (static) library dependencies
# lib_static_findlibs : the (static) library dependencies resolving

lib_static_templates_cmake_sublevel = {
'libs':
" {lib_target}"
,
'defs':
"{lib_static_findlibs}"
"""
add_library({lib_target} STATIC {lib_static_files})
target_include_directories({lib_target}
  PUBLIC {lib_static_pub_dirs}
  PRIVATE {lib_static_priv_dirs}
)
target_link_libraries({lib_target} {lib_static_libs})
"""
}

# lib_cmake_name : the name of the library to be found
# lib_cmake_path : the path where to find the associated cmake module
# lib_cmake_components : the cmake components to load with this library

lib_cmake_templates_cmake_sublevel = {
#TODO: with cmakev3, the following would be clean, but add_library(INTERFACE) doesn't exist before.
#so we do not do anything, the mess is done in user_sources.py instead.
# 'defs':
# """
# SET(CMAKE_MODULE_PATH {lib_cmake_path} ${{CMAKE_MODULE_PATH}})
# find_package({lib_cmake_name} REQUIRED {lib_cmake_components})
# add_library({lib_target} INTERFACE)
# target_link_libraries({lib_target} INTERFACE ${{{lib_cmake_name}_LIBRARIES}})
# target_include_directories({lib_target} INTERFACE ${{{lib_cmake_name}_INCLUDE_DIRECTORIES}})
# """
# ,
# 'libs':
# " {lib_target}"
}


def static_library(visitor, l, d):
    if l._qname in d['_seen']:
        return
    d['_seen'].add(l._qname)
    #children first to ensure dependences are already defined.
    visitor.node_bf(l, d)
    #collect the sources to be built
    srcs, dirs, libs, find_libs = gather_user_files(l['CXX'])
    d.update(lib_target = qn.cmake_userlib(l),
             lib_static_files = srcs,
             lib_static_pub_dirs = gather_user_header_paths(l),
             lib_static_priv_dirs = dirs,
             lib_static_libs = libs,
             lib_static_findlibs = find_libs)

    app(d, lib_static_templates_cmake_sublevel)


def cmake_library(visitor, l, d):
    if l._qname in d['_seen']:
        return
    d['_seen'].add(l._qname)
    #children first to ensure dependences are already defined.
    visitor.node_bf(l, d)
    d.update(lib_target = qn.cmake_userlib(l),
             lib_cmake_name = l['CMAKE_MODULE']._val,
             lib_cmake_path = '${CMAKE_CURRENT_LIST_DIR}' / user_src_path / wd.of(l),
             lib_cmake_components = listjoin(' ', (c._val for c in l['CMAKE_COMPONENTS']))
             )

    app(d, lib_cmake_templates_cmake_sublevel)

def module_settings(visitor, ms, d):
    #children first to ensure dependences are already defined.
    visitor.node_bf(ms, d)
    #collect the sources to be built
    srcs, dirs, libs, find_libs = gather_user_file(ms)
    d.update(module_sources = srcs,
             module_includes = dirs,
             module_libs = libs,
             module_find_libs = find_libs)

def do_pass(ast):

    d = {'namespace'       : ast._name,
         'package_name'    : qn.package_ast(ast),
         'ast'             : qn.cmake_ast(ast),
         'ast_fun'         : qn.c_astfun(ast),
         'user_src_folder' : user_src_path,
         'module_sources'  : '',
         'module_includes' : '',
         'module_libs'     : '',
         'module_find_libs': ''}

    # Generate the package file
    build_deps = ['radl_lib']
    for p in infos.loaded_modules:
        build_deps.append(qn.package_ast(p))

    d['ast_deps'] = ' '.join(build_deps)

    astfolder = ws_path(d['package_name'])

    # Generate the ast files
    c_filename, c_file, h_filename, h_file = ASTdump.gen(ast)
    d['ast_c_filename'] = c_filename
    d['ast_h_filename'] = h_filename
    write_file(astfolder / c_filename, c_file)
    write_file(astfolder / 'include' / h_filename, h_file)


    clear(d, cmake_templates)
    clear(d, lib_static_templates_cmake_sublevel)
    clear(d, lib_cmake_templates_cmake_sublevel)


    visitor = AstVisitor(fun_dict_of((module_settings, static_library, cmake_library)),
                         onleaf=follow_modlocal_links(AstVisitor.leaf_bf),  # @UndefinedVariable
                         kind='bf')
# We follow links to have correct dependencies, but we need unicity
    d['_seen'] = set()

    visitor.node_bf(ast, d) #visitor follow links and unique passage

    app(d, cmake_templates)


    # Generate the cmake file
    cmake = d['cmakelists']
    cmake_file = astfolder / 'CMakeLists.txt'
    write_file(cmake_file, cmake)


    catkin_pkg.gen(astfolder, d['package_name'], build_deps, [])



    user_src = astfolder / d['user_src_folder']
    link_path(user_src, infos.module_base_path, relative=infos.relative_links)



