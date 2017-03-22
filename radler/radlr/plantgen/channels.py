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

Created on Nov, 2014

@author: Léonard Gérard leonard.gerard@sri.com

This pass is in charge of defining the communication channels.

A communication channel is a node one to one communication,
computed from the logical communication description using subscriptions and
publications of topics.

Channels are stored in plantinfo.channels and is a mapping from
subscription/publication to a list of channels.

'''
from copy import copy
from math import floor

from radler import instrumentation
from radler.astutils import tools
from radler.astutils.tools import id_generator
from radler.radlr import types, infos
from radler.radlr.errors import internal_error, error
from radler.radlr.gen_utils import qn
from radler.radlr.types import StructType


#####
# Helper functions allowing coherent computations with respect to channels
def max_stale_steps(pub_period, channel_maxlatency, sub_period, pub_each, pub_wcet=None):
    """ This function main purpose is to help compute the mailboxes timeout
    flag. The idea is to count the number of consecutive steps where the mbox
    is stale. This count should never be more than the value we return.
    If the publisher WCET is given, the computed value may be more precise,
    otherwise, we assume the WCET is smaller than its period.
    """
    if pub_wcet == None:
        pub_wcet = pub_period
    return floor((pub_period * pub_each + pub_wcet + channel_maxlatency) / sub_period)


#####
# Channel kinds

kinds = ['kestrel_linux_ipc',
         'kestrel_certikosVM_ivc',
         'kestrel_lynxsecureVM_ivc',
         'kestrel_linux_ip']

class kestrel_linux_ipc:
    def __init__(self):
        pass
    def reverse(self):
        return copy(self)

class kestrel_certikosVM_ivc(id_generator):
    def __init__(self, vm, other_vm, plantinfo):
        self.myvm = plantinfo[vm]['vm_id']
        self.othervm = plantinfo[other_vm]['vm_id']
    def reverse(self):
        r = copy(self) #copy is needed to ensure same id
        r.myvm = self.othervm
        r.othervm = self.myvm
        return r

class kestrel_lynxsecureVM_ivc(id_generator):
    def __init__(self, vm, other_vm, plantinfo):
        self.id = kestrel_lynxsecureVM_ivc.gen_id()
        self.myvm = plantinfo[vm]['vm_id']
        self.othervm = plantinfo[other_vm]['vm_id']
        self.region_name = "SHMEM" + str(self.id)
    def reverse(self):
        r = copy(self) #copy is needed to ensure same id
        r.myvm = self.othervm
        r.othervm = self.myvm
        return r

class kestrel_linux_ip():
    def __init__(self, mac, other_mac):
        try:
            self.myip = mac['OS']['IP']._val
        except: #TODO: 6 when actual checking of channels is done move somewhere else.
            error("IP address is needed for communication to {}"
                  "".format(mac['OS']._qname), mac['OS']._location)
        try:
            self.otherip = other_mac['OS']['IP']._val
        except: #TODO: 6 when actual checking of channels is done move somewhere else.
            error("IP address is needed for communication to {}"
                  "".format(other_mac['OS']._qname), other_mac['OS']._location)
    def reverse(self):
        r = copy(self) #copy is needed to ensure same id
        r.myip = self.otherip
        r.otherip = self.myip
        return r

def chan_kind(src, dest, topic, incoming, plantinfo):
    """
    @param incoming may be True or False for outgoing channels
    It is expected that we are the destination (dest).
    """
    src_sys = plantinfo[src]['system']
    src_mac = plantinfo[src_sys]['machine']
    dest_sys = plantinfo[dest]['system']
    dest_mac = plantinfo[dest_sys]['machine']

    if src_sys._kind != 'linux' or dest_sys._kind != 'linux':
        internal_error("for now only linux to linux channels.")

    if src_sys == dest_sys:
        if src_mac != dest_mac:
            internal_error("same system on two machines")
        return kestrel_linux_ipc()
    elif (src_mac._kind == 'lynxsecure_vm'
          and dest_mac._kind == 'lynxsecure_vm'):
        src_lynx = plantinfo[src_mac]['hypervisor']
        dest_lynx = plantinfo[dest_mac]['hypervisor']
        if src_lynx == dest_lynx:
            return kestrel_lynxsecureVM_ivc(dest_mac, src_mac, plantinfo)
        else:
            return kestrel_linux_ip(dest_mac, src_mac)
    elif (src_mac._kind == 'certikos_vm'
          and dest_mac._kind == 'certikos_vm'):
        src_cos = plantinfo[src_mac]['hypervisor']
        dest_cos = plantinfo[dest_mac]['hypervisor']
        if src_cos == dest_cos:
            return kestrel_certikosVM_ivc(dest_mac, src_mac, plantinfo)
        else:
            return kestrel_linux_ip(dest_mac, src_mac)
    else:
        return kestrel_linux_ip(dest_mac, src_mac)


#####
# Channel high level

class channel(id_generator):
    def __init__(self, sub, pub, maxlatency, each, topic, plantinfo):
        """
        incoming may be True or False for outgoing channels.
        Channels expect to be created from the sub side.
        """
        self.id = channel.gen_id()
        self.sub = sub
        self.pub = pub
        self.maxlatency = maxlatency
        self.each = each
        self.topic = topic
        self.incoming = True
        self.kind = chan_kind(pub, sub, topic, self.incoming, plantinfo)
        # The data type and value of the topic are coming from the ast dump
        self.data_typename = qn.c_typename(topic)
        self.data_init_valname = qn.c_ast_val(topic)
        #The actual message encapsulate the data and adds radl fields:
        fields = [('radl__flags', 'uint8'), ('radl__data', types.of(topic))]
        if infos.instrument_msg_timings:
            fields += instrumentation.msg_timings.msg_field_decl()
        self.msg_type = StructType(False, fields)

    def reverse(self):
        r = copy(self)
        r.incoming = not self.incoming
        r.kind = self.kind.reverse()
        return r


def compute_channels(node, plantinfo):
    """ To compute the channels, we go over the subscriptions which are in a
     one to one relation with channels since the whole system is described.
    """
    def add(suborpub, c):
        if not (suborpub in plantinfo.channels):
            plantinfo.channels[suborpub] = [c]
        else:
            plantinfo.channels[suborpub].append(c)

    for sub in node['SUBSCRIBES']:
        t = sub['TOPIC']
        npub = plantinfo[t].get('publisher_node', None)
        pub = plantinfo[t].get('publisher', None)
        if (npub == None) or (pub == None):
            error("Node {} subscribes to {} which has no publisher in the plant."
                  "".format(node, t), node._location)
        each = int(pub['EACH']._val) if pub['EACH'] else 1
        c = channel(node, npub, int(sub['MAXLATENCY']._val), each , t, plantinfo)
        #Store the channel in the sub and the reverse channel in the pub
        add(sub, c)
        add(pub, c.reverse())


def do_pass(plantinfo):
    """ For each node in the plant describe by plantinfo, compute the channels
    associated with their subscriptions and publications.
    Channels are stored in plantinfo.channels and is a mapping from
    subscription/publication to a list of channels.
    """
    plantinfo.channels = tools.DictfromField('_qname')()
    for n in plantinfo.nodes:
        compute_channels(n, plantinfo)
