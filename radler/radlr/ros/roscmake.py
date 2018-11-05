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

Generate the cmake and the nodes associated (see the call to gennode)

'''

from pathlib import Path

from radler.astutils.tools import write_file, listjoin, relative_path
from radler.radlr import infos
from radler.radlr.gen_utils import qn
from radler.radlr.gen_utils.user_sources import    gather_node_user_file
from radler.radlr.rast import AstVisitor, follow_links
from radler.radlr.ros.rosnode import gennode


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


## cmake (top) level
#
# module : the module name
# find_modules : the modules to be found with catkin
# run_modules : the modules to add as run dependencies of this package


cmake_templates = {
'cmakeliststxt': """
cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_FLAGS "${{CMAKE_CXX_FLAGS}} -std=c++14")

project({module})

find_package(ament_cmake REQUIRED)
{find_modules_pkg}
{ros_modules_pkg}
find_package(rmw_implementation REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(rosidl_default_runtime REQUIRED)
find_package(rosidl_typesupport_cpp REQUIRED)

add_definitions(-DIN_RADL_GENERATED_CONTEXT)
"""
"{msgs_gen}"
"""

include_directories(
  include
  PRIVATE 
{inc_dir}
)"""
"{node_defs}"
"""

ament_export_dependencies(rosidl_default_runtime)

ament_package()

install(TARGETS
  {to_install}
  ARCHIVE DESTINATION lib 
  LIBRARY DESTINATION lib 
  RUNTIME DESTINATION bin 
)

install(FILES
  {extra_files}
  DESTINATION share 
)
"""
}

# To be applied only if msg_files is not empty
# msg_files : the msg files to be generated

cmake_msgs_templates = {
'msgs_gen':"""
rosidl_generate_interfaces({module}
  {msg_dir}/{msg_files}
)
"""
}

## node level
#
# node_name : the node name
# node_target : the node target name
# node_h_filename : the generated header filename
# node_dirs : the node include directories
# node_sources : the node executable sources
# node_libs : the node libraries needed to build it
# node_find_libs : the node libraries dependency resolving

node_templates_cmake_sublevel = {
'to_install':
" {node_target}"
,
'node_defs':"""
#get_target_property({node_user_src_var} {node_module_lib} radl_user_src)
set({node_user_src_var} "/tmp/catkin_ws/src/radlast_6_pubsub/user_src")"""
"{node_find_libs}"
"""
add_executable({node_target} {node_sources})
set_target_properties({node_target} PROPERTIES OUTPUT_NAME {node_name})
target_include_directories({node_target} PUBLIC {node_dirs} PRIVATE {node_gen_folder})
target_compile_definitions({node_target}
  PRIVATE RADL_MODULE_NAME={node_modulename}
  PRIVATE RADL_MODULE={node_module_ast_fun}\(\)
  PRIVATE RADL_NODE_NAME={node_name}
  PRIVATE RADL_NODE_QNAME={node_qname}
  PRIVATE RADL_HEADER="{node_h_filename}"
  PRIVATE RADL_STATE={node_user_state_type}
  PRIVATE RADL_STEP_FUN={node_user_step_fun}
  PRIVATE RADL_INIT_FUN={node_user_init_fun}
  PRIVATE RADL_FINISH_FUN={node_user_finish_fun}
)
target_link_libraries({node_target}
  {target_link_libs} {node_libs}
)
rosidl_target_interfaces({node_target}
      {module} "rosidl_typesupport_cpp")
"""
}


def _from_node(visitor, node, d):
    nodemodule = node._qname.rootmodule()
    d['node_name'] = node._name
    d['node_qname'] = str(node._qname)
    d['node_modulename'] = nodemodule.name()
    d['node_module_lib'] = qn.cmake_ast(nodemodule)
    d['node_target'] = qn.cmake_rosnode(node)
    d['node_module_ast_fun'] = qn.c_astfun(nodemodule)
    d['node_user_state_type'] = qn.c_user_state(node)
    d['node_user_step_fun'] = qn.c_user_step(node)
    d['node_user_init_fun'] = qn.c_user_init(node)
    d['node_user_finish_fun'] = qn.c_user_finish(node)

    node_h_path, node_cpp_path = gennode(node)
    d['node_h_filename'] = node_h_path.name
    d['node_sources'] = str(relative_path(node_cpp_path, d['_localroot']))
    d['node_gen_folder'] = str(relative_path(node_h_path.parent, d['_localroot']))

    d['node_user_src_var'] = qn.cmake_user_src(node)
    user_src_path = Path("${" + d['node_user_src_var'] + "}")

    srcs, dirs, libs, find_libs = gather_node_user_file(node, user_src_path)
    d['node_dirs'] = dirs
    d['node_sources'] += srcs
    d['node_libs'] = libs
    d['node_find_libs'] = find_libs

    target_link_libs = ''
    target_link_libs += '${{{0}_LIBRARIES}}\n'.format(qn.cmake_ast(nodemodule))
    target_link_libs += '${radl_lib_LIBRARIES}\n'
    target_link_libs += '${rclcpp_LIBRARIES}\n'
    for p in infos.loaded_modules:
        target_link_libs += '${{{0}_LIBRARIES}}\n'.format(qn.cmake_ast(p))

    d['target_link_libs'] = target_link_libs

    app(d, node_templates_cmake_sublevel)


def gen(localroot, msg_list, msg_dir, ast, extra_files=None):

    onleaf = AstVisitor.leaf_bf  # @UndefinedVariable

    visitor = AstVisitor({'node' : _from_node}, kind='bf', onleaf=onleaf)

    d = {'module'     : ast._name,
         'module_lib' : qn.cmake_ast(ast._qname.rootmodule()),
         'ast_fun'    : qn.c_astfun(ast),
         '_localroot' : localroot
         }

    clear(d, cmake_templates)
    clear(d, cmake_msgs_templates)
    clear(d, node_templates_cmake_sublevel)

    visitor.visit(ast, d)

    toload = infos.loaded_modules
    loaded_modules = ' '.join(qn.cmake_ast(n) for n in toload)

    d['find_modules'] = d['module_lib'] + ' radl_lib rclcpp ' + loaded_modules
    find_modules_pkg = ''
    find_modules_pkg += 'find_package({0} REQUIRED)\n'.format(qn.cmake_ast(ast._qname.rootmodule()))
    find_modules_pkg += 'find_package(radl_lib REQUIRED)\n'
    find_modules_pkg += 'find_package(rclcpp REQUIRED)\n'
    for p in toload:
        find_modules_pkg += 'find_package({0} REQUIRED)\n'.format(qn.cmake_ast(p))
    d['find_modules_pkg'] = find_modules_pkg

    inc_dir = ''
    inc_dir += '${{{0}_INCLUDE_DIRS}}\n'.format(qn.cmake_ast(ast._qname.rootmodule()))
    inc_dir += '${radl_lib_INCLUDE_DIRS}\n'
    inc_dir += '${rclcpp_INCLUDE_DIRS}\n'
    for p in toload:
        inc_dir += '${{{0}_INCLUDE_DIRS}}\n'.format(qn.cmake_ast(p))
        inc_dir += '${{{0}_INCLUDE_DIRS}}\n'.format(p)
    inc_dir += 'src'
    d['inc_dir'] = inc_dir

    d['run_modules'] = ' rclcpp'

    d['ros_modules'] = ' '.join(n.name() for n in toload)
    ros_modules_pkg = ''
    for p in toload:
        ros_modules_pkg += 'find_package({0} REQUIRED)\n'.format(p)
    d['ros_modules_pkg'] = ros_modules_pkg

# Trying to be smart make dependencies hard since otherwise we can't blindly
# add any ros package as a message dependency.
#     if len(msg_list) > 0:

    msg_files = (str(relative_path(m, msg_dir)) for m in msg_list)
    d['msg_files'] = listjoin(' ', msg_files)
    d['msg_dir'] = msg_dir
    d['extra_files'] = listjoin(' ', extra_files) if extra_files else ''
#    d['find_modules'] += ' message_generation'
#    d['run_modules'] += ' message_runtime'

    app(d, cmake_msgs_templates)

    app(d, cmake_templates)

    write_file(localroot / "CMakeLists.txt", d['cmakeliststxt'])


