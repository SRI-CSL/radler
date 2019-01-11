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
from radler.astutils.tools import ensure_dir
from radler.radlr import infos
from radler.radlr.gen_utils import catkin_pkg
from radler.radlr.ros import rosmsg, roscmake, rosutils, rosplant
from radler.radlr.workspace import ws_rospath
from radler.radlr.gen_utils import qn

def do_pass(ast, plantinfo):

    package_name = ast._name
    package_folder = ws_rospath(package_name)
    msg_folder = rosutils.msg_folder(package_folder)
    ensure_dir(msg_folder) # Catkin is not happy without a msg folder

    # Generate the package.xml file
    build_deps = ['rmw_implementation', 'rclcpp', 'radl_lib', 'std_msgs']
    run_deps = ['rosidl_default_runtime', 'rclcpp', 'std_msgs']

    # Modular compilation, we have to add dependencies
    for p in infos.loaded_modules:
        build_deps.append(p)
        build_deps.append(qn.cmake_ast(p))

    build_deps.append(qn.cmake_ast(ast._qname.rootmodule()))

    catkin_pkg.gen(package_folder, package_name, build_deps, run_deps)

    # Generate the message files
    msg_list = rosmsg.generate_package_msg_files(package_folder, package_name, ast)

    extra_files = []
    if (plantinfo):
        extra_files += rosplant.gen_launchfiles(plantinfo, package_name, package_folder)
#        extra_files += [rosplant.gen_srosfile(plantinfo, package_name, package_folder)]

    # Generate the nodes and cmake file
    roscmake.gen(package_folder, msg_list, msg_folder, ast, extra_files)
