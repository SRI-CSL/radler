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

Compute WCET of a node step function from step_timings

@author: Léonard Gérard leonard.gerard@sri.com

'''

from collections import OrderedDict
from math import sqrt
import re

from radler.astutils.tools import Bunch
from radler.radlr.errors import internal_error


class StreamStats:
    """
    Welford's algorithm computes the sample variance incrementally.
    """

    def __init__(self, value_printer=str):
        self.n = 0
        self.mean = 0
        self.M2 = 0
        self.min = 0
        self.max = 0
        self.first_time = True
        self.value_printer = value_printer

    def add(self, x):
        self.n = self.n + 1
        delta = x - self.mean
        self.mean += delta / self.n
        self.M2 += delta * (x - self.mean)
        if self.first_time:
            self.min = x
            self.max = x
            self.first_time = False
        else:
            if self.min > x : self.min = x
            if self.max < x : self.max = x

    @property
    def std_deviation(self):
        return 0 if self.n <2 else sqrt(self.M2/(self.n - 1))

    def __str__(self):
        return ("min: {}  M: {}  max: {}  (SD: {} N: {})"
                "".format(self.value_printer(self.min),
                          self.value_printer(self.mean),
                          self.value_printer(self.max),
                          self.value_printer(self.std_deviation), self.n))

def _update_time():
    return '    _instr_time = radl_gettime();'

def init_hook():
    return '  radl_duration_t _instr_time;\n'

def step_start_hook():
    return _update_time()

def step_done_hook():
    return _update_time()



def instrument_print(instrname, key, string, args = ()):
    fmt = '"__i%" RADL_PRItime "({})[{}]{}\\n"'.format(instrname, key, string)
    fargs = ', '.join(('_instr_time',) + args)
    return ('    RADL__PRINTF({},{});\n'.format(fmt, fargs))

instrument_re = re.compile(r"__i(\d+)\((msg_timings|step_timings)\)\[(\S*)\](.*)")


def data_warning(node_name, tool_name, msg):
    print("Data error for {} ({}): {}".format(node_name, tool_name, msg))

def print_timing(time):
    """ Assumes the time provided is in nanoseconds.
    Returns 4 meaning full digits.
    """
    if time < 1000:
        return "{:>5.4g}nsec".format(time)
    elif time < 1000000:
        return "{:>5.4g}usec".format(time/1000)
    elif time < 1000000000:
        return "{:>5.4g}msec".format(time/1000000)
    else:
        return "{:>5.4g}sec".format(time/1000000000)


class step_timings:
    def __init__(self, stats_class):
        self.during_call = -1
        self.last_call_time = 0
        self.wcet_stats = stats_class(print_timing)
        self.period_stats = stats_class(print_timing)

    @staticmethod
    def print_entering(node_qn):
        return (_update_time() + '\n'
                + instrument_print("step_timings", node_qn, "1"))
    @staticmethod
    def print_exiting(node_qn):
        return (_update_time() + '\n'
                + instrument_print("step_timings", node_qn, ""))

    def push(self, time, node_name, entering):
        """ The provided time values need to be positive and increasing."""
        if entering == '1':
            if self.during_call == 0:
                self.period_stats.add(time - self.last_call_time)
            self.during_call = 1
            self.last_call_time = time
        else:
            if self.during_call != 1:
                data_warning(str(node_name), 'step_timings', 'exiting at {} without previous entering, data point discarded'.format(time))
                return
            self.wcet_stats.add(time - self.last_call_time)
            self.during_call = 0

    def __str__(self):
        return ("Stepping: {}\nPeriod:   {}"
                "".format(self.wcet_stats, self.period_stats))


class msg_timings:

    @staticmethod
    def msg_field_decl():
        return [('radl__instr_cpt', 'uint32'),
                ('radl__instr_timestamp', 'time')]

    @staticmethod
    def msg_pub_hook(topic_qn, pubname, msg_c_variable):
        r = ('    static unsigned int {cpt} = 1;\n'
             '    {msgvar}->radl__instr_cpt = {cpt}++;\n'
             '    {msgvar}->radl__instr_timestamp = _instr_time;\n'
             ''.format(msgvar=msg_c_variable, cpt='_instr_cpt_' + pubname,
                       cpt_t = 'unsigned int'))
        return r

    @staticmethod
    def msg_sub_hook(topic_qn, node_qn, subname, msg_c_variable):
        cpt = '_instr_cpt_'+subname
        fmt = '{}(%" RADL_PRItime ",%u)'.format(topic_qn)
        farg = (msg_c_variable + '->radl__instr_timestamp',
                msg_c_variable + '->radl__instr_cpt')
        instp = instrument_print('msg_timings', str(node_qn), fmt, farg)
        r = ('    static unsigned int {cpt} = 1;\n'
             '{instp}'
             '    {cpt}++;\n'
             ''.format(cpt=cpt, instp=instp))
        return r

    sub_regex = re.compile(r'(\S+)\((\d+),(\d+)\)')

    def __init__(self, stats_class):
        self.topics = OrderedDict()
        self.stats_class = stats_class

    def record_topic(self, topic_qn):
        d = Bunch(latency=self.stats_class(print_timing),
                  dropped=0, late=0, stale=0, last_cpt=0)
        self.topics[topic_qn] = d
        return d

    def push(self, time, node_name, msg):
        """ The provided time values need to be positive and increasing."""
        m = self.sub_regex.match(msg)
        if not m:
            data_warning(node_name, 'msg_timings', 'incorrect log line {} at {}'.format(msg, time))
            return

        (topic, pub_time, pub_cpt) = m.groups()
        pub_time = int(pub_time)
        pub_cpt = int(pub_cpt)

        t = self.topics.get(topic, None)
        if not t:
            t = self.record_topic(topic)

        if pub_cpt <= 0:  # Check whether the publisher is started
            return

        if pub_cpt == t.last_cpt:  # Stale sub
            t.stale += 1
            return

        #--- It is a new message
        t.latency.add(time - int(pub_time))
        if pub_cpt < t.last_cpt:  # Overtaking case
            t.late += 1
        else:  # Normal case where the msg is new and increasing
            t.dropped += pub_cpt - t.last_cpt - 1
            t.last_cpt = pub_cpt

    def __str__(self):
        r = ''
        for (n, t) in self.topics.items():
            r += ("-Topic: {}\n  Latency: {}\n"
                  "  Late: {}  Dropped: {}  Stale: {}\n"
                  "".format(n, t.latency, t.late, t.dropped, t.stale))
        return r



instruments = {'step_timings' : step_timings,
               'msg_timings'  : msg_timings}

class analyzer:

    def __init__(self, instruments_to_use, nodes_to_track, stats_class=StreamStats):
        """
        @argument instruments_to_use is the list of instruments to use.
        @argument nodes_to_track is expected to be a list of node qualified names.
        If the empty list is provided, nodes will be discovered on the fly.
        """
        self.newnodesonthefly = (nodes_to_track is None)
        self.stats_class = stats_class
        self.nodes = OrderedDict()
        self.il = dict()
        # Resolve instrument classes
        try:
            for i in instruments_to_use:
                self.il[i] = instruments[i]
        except AttributeError:
            internal_error("Unknown analyser.")

        # Initialize all the analyzer statically known
        if not self.newnodesonthefly:
            for n in nodes_to_track:
                self.record_node(n)

    def record_node(self, n):
        node_insts  = dict((i, ic(self.stats_class)) for (i,ic) in self.il.items())
        self.nodes[str(n)] = node_insts
        return node_insts

    def parse(self, line):
        m = instrument_re.match(line)
        if not m:
            return # this line is not a well formed instrument log

        (time, instrument, node_qn, msg) = m.groups()

        if not (instrument in self.il):
            return # We are not using this instrument

        node_insts = self.nodes.get(node_qn, None)
        if node_insts is None:
            if self.newnodesonthefly:
                node_insts = self.record_node(node_qn)
            else:
                return # We are not analyzing this node

        time = int(time)

        inst = node_insts[instrument]
        inst.push(time, node_qn, msg)

    def __str__(self):
        r = ''
        for (n,nis) in self.nodes.items():
            r += "-----Node: " + n + '\n'
            for i in self.il.keys():
                s = str(nis[i])
                if s:
                    s += '\n'
                r += "---" + i + '\n' + s
            r += '\n'
        return r


