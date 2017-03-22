#!/bin/bash
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

SCRIPT_DIR=`dirname $(python -c "import os, sys; print(os.path.realpath(\"$0\"))")`

PYTHONPATH="$SCRIPT_DIR/external_libs/parsimonious:$SCRIPT_DIR/external_libs/pydot:$SCRIPT_DIR" python3.4 $SCRIPT_DIR/radler/main.py "$@"
