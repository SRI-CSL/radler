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

Created on Mar, 2015

@author: Léonard Gérard leonard.gerard@sri.com
'''

from sys import stdout
import json

from radler.radlr import types, language
from radler.radlr.rast import AstVisitor, follow_links


def reduce(astnode, filter_pred):
    def default(visitor, n, _):
        t = types.of(n)
        if isinstance(t, str): # Basic value
            return language.interpret_value(t, n._val), _
        else:
            return (str(n._qname), visitor.visit(filter_pred(n._children), _)[0]), _
    def array(visitor, a, _):
        return (str(a._qname), [visitor.visit(x, _)[0] for x in a['VALUES']]), _
    def struct(visitor, s, _):
        return (str(s._qname), {x._name: visitor.visit(x, _)[0] for x in s['FIELDS']}), _
    visitor = AstVisitor({'array':array, 'struct':struct, 'topic':struct},
                         default=default,
                         onleaf=follow_links(AstVisitor.leaf_mapacc), #@UndefinedVariable
                         kind='mapacc')
    return visitor.visit(astnode, ())[0]


def to_json(plant, filter_pred):
    json.dump(reduce(plant, filter_pred), stdout, indent=2)



logical_fields = {'MACHINES', 'OS', 'VMS', 'NODES', 'PUBLISHES',
                      'SUBSCRIBES', 'PERIOD', 'WCET', 'TOPIC', 'MAXLATENCY', 'FIELDS'}

def logical(d):
    if isinstance(d, dict):
        return { k: v for (k, v) in d.items() if k in logical_fields}
    else:
        return d



dump_filters = { "none" : lambda x:x, "logical" : logical}
dump_formatters = { "json" : to_json }
