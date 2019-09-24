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


Generate one ROS .msg file per topic and struct type.
If a struct as a EXTERNAL_ROS_DEF field, it is used instead of generating
a new one.
'''

from radler import instrumentation
from radler.astutils.tools import write_file
from radler.radlr import types, infos, language
from radler.radlr.errors import internal_error
from radler.radlr.gen_utils import qn
from radler.radlr.rast import AstVisitor, follow_links
from radler.radlr.ros.rosutils import msg_cpp_qname, msg_cpp_header, msg_msg_file, \
    msg_ros_qname
from radler.radlr.types import StructType, ArrayType

import os
import subprocess
from pathlib import Path

def struct_of_topic(struct_t):
    """ It adds the header fields used for ros topics """
    fields = [('radl_flags', 'uint8')]
    fields += struct_t.elems_t
    if infos.instrument_msg_timings:
        fields += instrumentation.msg_timings.msg_field_decl()
    return StructType(False, fields)


def collect(package_folder, package_name, ast, generate_all):
    """ return a set of struct types to be generated.
    It is not to be generated if it has a field EXTERNAL_ROS_DEF,
    or if it is already in infos.ros_types.
    """
    def _st(visitor, node, s):
        """ s is a mapping between names and filepath of messages to generate.
        """
        if node._kind == 'topic': #special treatment to add private fields
            t = struct_of_topic(types.of(node))
        else:
            t = types.of(node)
        ext_rd = node['EXTERNAL_ROS_DEF']
        if ext_rd: #External def to be used
            name = ext_rd['FULLNAME']._val
            header = ext_rd['HEADER']._val
        else:
            reg_name = infos.ros_type_of_struct.get(t, None)
            if not reg_name: #Msg name and file to create
                msgname = qn.rosmsg(node)
                s[t] = msg_msg_file(package_folder, msgname)
                msgpkg = package_name
                infos.ros_type_of_struct[t] = (msgpkg, msgname)
            else: #Msg file already created
                (msgpkg, msgname) = reg_name
            header = msg_cpp_header(msgpkg, msgname)
            #keep only the actual string to identify the type and header file
            name = msg_cpp_qname(msgpkg, msgname)
        #Store our findings in the node for future retrieval
        node._ros_msgtype_name = name
        node._ros_msgtype_header = header

        return visitor.node_red(node, s) #recursive call

    if generate_all:
        onleaf = onleaf=follow_links(AstVisitor.leaf_red)  # @UndefinedVariable
    else:
        onleaf = AstVisitor.leaf_red  # @UndefinedVariable

    visitor = AstVisitor({'topic': _st, 'struct' : _st}, kind='red', onleaf=onleaf)
    s = visitor.visit(ast, dict())
    return s


def ros_typename(t):
    if isinstance(t, str):
        tname = language.type_mapping[t]['ROS']
        return tname
    elif isinstance(t, ArrayType):
        return '{}[{}]'.format(ros_typename(t.elem_t), t.size)
    elif isinstance(t, StructType):
        return msg_ros_qname(*infos.ros_type_of_struct[t])
    else:
        internal_error("Unexpected type.")


def ros_msgdef(struct_t):
    elems = ('{} {}'.format(ros_typename(ft), fb)
                        for (fb, ft) in struct_t.elems_t)
    return '\n'.join(elems)


def generate_msg_files(msgtogen):
    """ The msgtogen is a mapping (dict) from the data StructType to the msg
    filename. The required extra msg fields (radl_flags, instrumentation, etc)
    are automatically added.
    @Returns the list of message files generated.
    """
    msgs = []
    #Generate the needed message files
    for (struct_t, file) in msgtogen.items():
        msgs.append(file)
        filecontent = ros_msgdef(struct_t)
        write_file(file, filecontent)

    return msgs

def generate_all_msg_files(package_folder, package_name, ast):
    """ Generate all the message files required for the provided ast,
    All of them are flattened in the specified package folder and name
    (Instead of generating each messages in their respective origin package).
    @Returns the list of message files generated.
    """
    msgtogen = collect(package_folder, package_name, ast, True)
    return generate_msg_files(msgtogen)

def generate_package_msg_files(package_folder, package_name, ast):
    """ Generate the messages defined in ast as being part of the provided
    package folder and name.
    @Returns the list of message files generated.
    """
    msgs = []
    if os.path.exists(str(infos.module_base_path) + '/../msg'):
        p=subprocess.call('cp -r ' + str(infos.module_base_path) + '/../msg ' + str(package_folder), shell=True)
    for root, dirs, files in os.walk(str(package_folder) + '/msg'):
        for f in files:
            msgs.append(Path(os.path.join(root, f)))

    msgtogen = collect(package_folder, package_name, ast, False)

    msgs += generate_msg_files(msgtogen)
    return msgs
