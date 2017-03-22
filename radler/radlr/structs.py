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

Verify struct and topic have named fields.
'''
from radler.radlr.errors import error
from radler.radlr.rast import Ident, AstVisitor


def onstruct(visitor, node, _):
    for f in node['FIELDS']:
        if isinstance(f, Ident):
            error("Struct and topic fields must be named.\n"
                  "No Ident allowed, only aliases.", f._location)

def do_pass(ast):
    visitor = AstVisitor({'struct': onstruct, 'topic': onstruct}, kind='bf')
    visitor.visit(ast)
