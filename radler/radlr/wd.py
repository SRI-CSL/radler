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

Working Directory module.

The pass adds a working directory attribute '_wd' to every nodes,
storing to the user path associated. All paths are Path from pathlib.

Once the pass is done, the main function is 'of'.
- To get the working directory, use wd.of(node). The returned path is absolute
only if the user specified it so.
- To get an absolute path, do infos.module_base_path / wd.of(node).
'''

from pathlib import Path

from radler.radlr.rast import AstVisitor


def _wd(visitor, node, wd):
    p = node.get('PATH', None)
    subdir = p._val if p else ''
    wd = wd / subdir
    node._wd = wd
    return visitor.node_bf(node, wd)

def do_pass(ast):
    """ Add a _wd attribute to nodes indicating current user path."""
    visitor = AstVisitor(default=_wd, kind='bf')
    visitor.visit(ast, Path())


def of(node):
    """This function return the user path of node.
    Note that the pass needs to have been done before any call to this fun.
    """
    return node._wd
