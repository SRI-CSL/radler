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

This pass transforms aliases into actual AST aliases.

Moreover, it calls update_idents, ensuring correctness of the references.
'''

from radler.radlr.errors import internal_assert
from radler.radlr.rast import AstVisitor, Ident, Alias
from radler.radlr.sanitize import update_idents


def do_pass(ast, root_namespace):
    """ Transform alias nodes into leafs of type Alias,
    behaving like the Ident it points to.
    This has to be done with a frozen ast or extra care is needed after this.
    """
    def _alias(visitor, node, _):
        internal_assert(len(node._children)==1, "incorrect alias node")
        ident = node._children[0]
        internal_assert(isinstance(ident, Ident), "incorrect alias node")
        a = Alias(node._qname, node._location, ident)
        return a, _
    visitor = AstVisitor({'_alias': _alias},
                         inplace=True, kind='mapacc')
    visitor.visit(ast, ())
    update_idents(ast, root_namespace)
