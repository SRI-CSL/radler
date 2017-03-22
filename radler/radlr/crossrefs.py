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


Add declared publisher to the topic publisher internals.
Add declared subscribers to the topic subscribers internals.
Add their system to nodes.
Add their hypervisor to vms.
Define whether a node is C or CXX.

'''

from radler.radlr.errors import error
from radler.radlr.rast import AstVisitor
