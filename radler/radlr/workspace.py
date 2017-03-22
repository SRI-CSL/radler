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

Created on Dec 16, 2014

@author: lgerard

'''

from radler.astutils.tools import link_path
from radler.radlr import infos


def ws_path(relative_filepath):
    return infos.ws_dir / relative_filepath

def ws_link_pervasives():
    link_path(ws_path('radl_lib'), infos.lib_dir, relative=infos.relative_links)
    link_path(ws_path('radlast_4_radl'), infos.radl_module(), relative=infos.relative_links)

def ws_rospath(relative_filepath):
    return infos.ws_dir / 'ros' / relative_filepath

def ws_link_rospervasives():
    link_path(ws_rospath('radl'), infos.radl_rosmodule())
