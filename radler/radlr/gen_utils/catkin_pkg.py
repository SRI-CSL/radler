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

from radler.astutils.tools import write_file
from radler.radlr import infos


package_xml_template = ("""<?xml version="1.0"?>
<package format="3">
  <name>{package}</name>
  <version>0.0.1</version>
  <description>Generated from {source}</description>
  <maintainer email="leonard.gerard@sri.com">Léonard Gérard</maintainer>
  <license>GPL</license>"""
"{build_deps}"
"""
  <buildtool_depend>ament_cmake</buildtool_depend>
  <buildtool_depend>rosidl_default_generators</buildtool_depend>
  <member_of_group>rosidl_interface_packages</member_of_group>
  <export>
    <build_type>ament_cmake</build_type>
  </export>"""
"{run_deps}"
"""
</package>
"""
)

run_dep_template = """
  <exec_depend>{package_dep}</exec_depend>"""

build_dep_template = """
  <build_depend>{package_dep}</build_depend>"""


def gen(package_folder, package_name, build_dependencies, run_dependencies):
    d = {'source'  : str(infos.source_file),
         'package' : package_name}

    build_deps = ''
    for p in build_dependencies:
        build_deps += build_dep_template.format(package_dep=p)
    d['build_deps'] = build_deps

    run_deps = ''
    for p in run_dependencies:
        run_deps += run_dep_template.format(package_dep=p)
    d['run_deps'] = run_deps

    package_xml = package_xml_template.format(**d)
    write_file(package_folder / "package.xml", package_xml)
