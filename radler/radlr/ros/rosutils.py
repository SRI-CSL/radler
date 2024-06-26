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

    Utilities to handle file paths, filenames, etc.
'''

from radler.radlr.errors import internal_error
from radler.radlr.workspace import ws_rospath
import re 

def qn_topic(qname):
    return qname.qname('/', root='/')


def qn_file(qname, prefix='', suffix=''):
    p = list(qname.pathwalk())
    if len(p) < 2:
        internal_error("trying to use a qn with size < 2 for file gen.")
    return ws_rospath('/'.join(p[0:-1]) + '/src/' + prefix + p[-1] + suffix)

def qn_srcfile(qname, prefix='', suffix=''):
    return qn_file(qname, prefix, suffix)

def node_package(qname):
    p = list(qname.pathwalk())
    if len(p) != 2:
        internal_error("trying to use a qn with size != 2 for package.")
    return p[0]

def msg_folder(package_folder):
    return package_folder / 'msg'

def msg_msg_file(package_folder, msg_name):
    return msg_folder(package_folder) / (msg_name + '.msg')

def demangle(s):
    pat = re.compile('^([A-Z])([a-zA-Z]+)(\d+)([A-Z])([a-zA-z]+)(\d+)([A-Z])([a-zA-Z]+)$', re.IGNORECASE)
    retval = None
    m =  pat.match(s)
    if m:
        retval = '{0}{1}{2}_{3}{4}{5}_{6}{7}'.format(m.group(1).lower(), m.group(2), m.group(3),
                                                     m.group(4).lower(), m.group(5), m.group(6),
                                                     m.group(7).lower(), m.group(8))
    return retval

def msg_cpp_header(msg_package_name, msg_name):
    msg_name = demangle(msg_name) 
    return msg_package_name + '/msg/' + msg_name + '.hpp'

def msg_cpp_qname(msg_package_name, msg_name):
    return msg_package_name + '::msg::' + msg_name

def msg_ros_qname(msg_package_name, msg_name):
    return msg_package_name + '/' + msg_name
