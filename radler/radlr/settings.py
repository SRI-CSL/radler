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

Created on Oct, 2014

@author: Léonard Gérard leonard.gerard@sri.com


Check and get the module setting object.

'''
from pathlib import Path

from radler.radlr import infos
from radler.radlr.errors import error
from radler.radlr.rast import AstVisitor


def module_settings(visitor, node, seen):
    if seen:
        error("Only one module_settings object is allowed per module.",
              node._location)
    mbp = node['MODULE_BASE_PATH']
    if mbp:
        infos.module_base_path /= Path(mbp._val)

def do_pass(ast):
    visitor = AstVisitor({'module_settings' : module_settings}, kind='red')
    visitor.visit(ast, False)
