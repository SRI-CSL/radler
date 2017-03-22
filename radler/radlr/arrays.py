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

Verify array values are coherent .

'''
from radler.radlr import types
from radler.radlr.rast import AstVisitor


def _tc_arrays(visitor, array, _):
    """Type Check arrays, simply call types.of() """
    types.of(array)
    return _

_tc_visitor = AstVisitor({'array' : _tc_arrays}, kind='red')

def typecheck(ast):
    _tc_visitor.visit(ast, ())
