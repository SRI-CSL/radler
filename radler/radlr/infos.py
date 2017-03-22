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

    Module used to store global properties.

    Useful to reduce useless passing of the global context,
but also to break circular dependencies since it depends on nothing.
'''

from pathlib import Path

from radler.astutils.names import RootNamespace


radler_version = '1.1'

calling_dir = None
"The directory where radler script was called (it is set by the main)."

script_dir = Path(__file__).absolute().parent.parent
"The radler Path directory."

lib_dir = script_dir / '..' / 'radl_lib'
"The radl lib Path directory."

pervasives_dir =  script_dir / '..' / 'pervasives'

# defined as a function because pervasives_dir may be changed by the command line
def radl_module(): return pervasives_dir / 'radlast_4_radl'
def radl_rosmodule(): return pervasives_dir / 'ros/radl'


##########
# Global properties concerning everything which is loaded
##########

root_namespace = RootNamespace()
"The global root namespace."

# Mostly used to reduce msg creation.
ros_type_of_struct = dict()
"Mapping from types to ROS msgs (a tuple package name, message name)."

c_typedecl = dict()
"Mapping from types to C type names."

publishers = dict()
"Mapping from topic qname to publisher (node) qname."

semantics = None
"Semantics object for the language. It is created during bootstrapping."


##########
# Global properties concerning the current source file.
##########

ast = None
"The program ast. Actually set by the parser."

ws_dir = None
"The destination Path directory"

source_file = Path()
"The source Path file."

loaded_modules = []
"The modules loaded to compile this module."

module_base_path = Path()
"The Path object used as root to every relative path written in this module."

relative_links = False

instrumentation = False
instrument_step_timings = False
instrument_msg_timings = False

