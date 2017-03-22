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

Created on Jan, 2015

@author: Léonard Gérard leonard.gerard@sri.com


This pass gather informations.

Currently gather the publisher information.

'''
from radler.astutils.nodetrees import fun_dict_of
from radler.radlr import infos
from radler.radlr.errors import warning
from radler.radlr.rast import AstVisitor


def node(visitor, node, _):
    for pub in node['PUBLISHES']:
        top = pub['TOPIC']
        if top._qname in infos.publishers:
            warning("Topic {} has multiple publishers."
                    "  -> Be cautious with the --ROS backend."
                    "".format(top), top._location)
        infos.publishers[top._qname] = node._qname


def do_pass(ast):
    v = AstVisitor(fun_dict_of((node,)), kind='bf')
    v.visit(ast, ())
