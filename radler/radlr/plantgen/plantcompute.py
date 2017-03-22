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

from radler.astutils import tools
from radler.radlr.errors import error
from radler.radlr.plantgen import channels
from radler.radlr.rast import AstVisitor, follow_links


def node(visitor, n, plantinfo):
    plantinfo.nodes.append(n)
    for p in n['PUBLISHES']:
        t = p['TOPIC']
        if not(t in plantinfo):
            plantinfo[t] = dict()
            plantinfo[t]['subscriber_nodes'] = list()
            plantinfo.topics.append(t)
        if 'publisher_node' in plantinfo[t]:
            error("Topic {} is published by {} and {} in the plant."
                  "".format(t, plantinfo[t]['publisher_node'], p), p._location)
        plantinfo[t]['publisher_node'] = n
        plantinfo[t]['publisher'] = p
    for s in n['SUBSCRIBES']:
        t = s['TOPIC']
        if not(t in plantinfo):
            plantinfo[t] = dict()
            plantinfo[t]['subscriber_nodes'] = list()
            plantinfo.topics.append(t)
        plantinfo[t]['subscriber_nodes'].append(n)
    visitor.node_bf(n, plantinfo)


def sys(visitor, s, plantinfo):
    for node in s['NODES']:
        if node in plantinfo:
            error("Node {} is used multiple times in the plant.".format(node),
                  node._location)
        plantinfo[node] = dict()
        plantinfo[node]['system'] = s
    visitor.node_bf(s, plantinfo)

def hypervisor(visitor, h, plantinfo):
    i = 0
    for vm in h['VMS']:
        i += 1
        if vm in plantinfo:
            error("VM {} is already in the plant.".format(vm), vm._location)
        plantinfo[vm] = dict()
        plantinfo[vm]['hypervisor'] = h
        plantinfo[vm]['vm_id'] = i
    visitor.node_bf(h, plantinfo)

def machine(visitor, m, plantinfo):
    plantinfo.machines.append(m)
    os = m['OS']
    if os in plantinfo:
        error("An OS may be used only once in a plant.", os._location)
    plantinfo[os] = dict()
    plantinfo[os]['machine'] = m
    visitor.node_bf(m, plantinfo)

def do_pass(plant):
    """ This pass follows the links up to the nodes which are the one defining
    the actual channels.
    """
    # Collect the needed information and the nodes to consider.
    v = AstVisitor({'node'          : node,
                    'linux'         : sys,
                    'lynxsecure'    : hypervisor,
                    'certikos'      : hypervisor,
                    'lynxsecure_vm' : machine,
                    'certikos_vm'   : machine,
                    'machine'       : machine },
                   onleaf=follow_links(AstVisitor.leaf_bf), #@UndefinedVariable
                   kind='bf')
    # Create a dict having ast nodes as keys (qnames),
    plantinfo = tools.DictfromField('_qname')()
    plantinfo.nodes = []
    plantinfo.topics = []
    plantinfo.machines = []
    plantinfo.plant = plant
    v.visit(plant, plantinfo)

    channels.do_pass(plantinfo)

    return plantinfo
