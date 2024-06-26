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

Generate one ROS _node.cpp file per node declaration.

'''

from radler import instrumentation
from radler.astutils.tools import write_file
from radler.instrumentation import msg_timings
from radler.radlr import infos
from radler.radlr.cgen.cutils import copy_to
from radler.radlr.errors import warning
from radler.radlr.gen_utils import qn
from radler.radlr.gen_utils.user_sources import user_node_class, \
    node_user_header_file, node_sources_type
from radler.radlr.plantgen.channels import max_stale_steps
from radler.radlr.ros.rosutils import qn_srcfile, qn_topic


templates = {
'node_cpp':
'''
/**
 * File Generated by raldr
**/

#include "rclcpp/rclcpp.hpp"
#include <functional>
#include <cmath>

#include "radl_roslib.hpp"
#include "{node_h_name}"
'''
"{include_user_header}"
"""

int main(int argc, char* argv[]) {{

  {node_module_init}();

  rclcpp::init(argc, argv);
  auto _h = rclcpp::Node::make_shared("{name}");

  rclcpp::Rate _node_rate({period});

  // set up publishers
  {set_pub}

  // set up subscribers
  {set_sub}

  //create outgoing structure filled with the default values
  {out_struct_type} _out;
  {out_fill}

  {out_flags_struct} _out_flags;

  {in_flags_struct} _in_flags;
  const {in_flags_struct} * const _pin_flags = &_in_flags;

  {in_struct_type} _in;
  const {in_struct_type} * const _pin = &_in;

"""
"{node_state_init}"
"{instruments_init}"
"""
  // Variables used by the loop
  radl_flags_t _gathered_flags;
  bool _is_stale;
  {timeout_counters}

  while (rclcpp::ok()) {{
    //combine incoming messages
    rclcpp::spin_some(_h);
    _gathered_flags = 0;
"""
"{instruments_start}"
"""

    {in_fill}
    {pub_flags_fill}
"""
"{node_step_call}"
"{instruments_done}"
"""
    {pub_call}
    _node_rate.sleep();
  }}
"""
"{node_state_finish}"
"""
  return 0;
}}

"""
, 'node_h':
"""
/**
 * File Generated by raldr
**/

#pragma once

#include "radl__lib.h"

#include "{node_module_header}"

{msg_include}

struct {out_struct_type} {{
  {out_struct_def}
}};

struct {in_struct_type} {{
  {in_struct_def}
}};

struct {in_flags_struct} {{
  {in_flags_struct_def}
}};

struct {out_flags_struct} {{
  {out_flags_struct_def}
}};

"""
, 'msg_include'       : '#include "{topic_file}"'
, 'out_struct_def'    : "{topic_t}* {pubname};"
, 'out_fill'          :
"""{topic_t} {initmsg};
  {init_msg_fill}
  _out.{pubname} = &{initmsg};"""
, 'pub_call'          :
"""// Use user flags and publish the message of {pubname}
    _out.{pubname}->radl_flags = _out_flags.{pubname};
"""
'{pub_hooks}'
"""
    {actionname}(*_out.{pubname});"""
, 'set_pub'           :
"""auto {actionname}_ros = _h->create_publisher<{topic_t}>("{topic_name}", rclcpp::SystemDefaultsQoS());{actiondef}"""
, 'in_struct_def'     : "{topic_t}::ConstSharedPtr {subname};"
, 'in_fill'           :
"""// Retrieve data for {subname} subscription
    _in.{subname} = {actionname}.value(&_is_stale);
    int _{subname}_maxstale = floor((_{subname}_maxperiod+_{subname}_maxlatency) / (1.0 / {period}));
    RADL__MNG_FLAGS({subname},_in.{subname}->radl_flags,_is_stale,_tc_{subname},_{subname}_maxstale)
"""
'{sub_hooks}'
, 'timeout_counters'  : "int _tc_{subname} = 0;"
, 'set_sub'           :
"""{topic_t}* {initmsg} = new({topic_t});
  {init_msg_fill}
  {topic_t}::ConstSharedPtr _wrap{initmsg}({initmsg});
  {actionclass}<{topic_t}> {actionname}(_wrap{initmsg});
  std::function<void (const {topic_t}::SharedPtr)> {actionname}_func;
  {actionname}_func = std::ref({actionname});
  auto {actionname}_ros = _h->create_subscription<{topic_t}>("{topic_name}", rclcpp::SystemDefaultsQoS(), {actionname}_func);

  double _{subname}_maxperiod = 10; // pub_period * pub_each + pub_wcet in seconds
/* TODO  
  if (!ros::param::get("{topic_name}/maxperiod", _{subname}_maxperiod)) {{
    ROS_ERROR("Topic {topic_name} maximum period is not provided (param {topic_name}/maxperiod), setting it to 10 seconds");
    _{subname}_maxperiod = 10;
  }} */
  double _{subname}_maxlatency = 0; // channel max latency in seconds
/* TODO  
  if (!ros::param::get("~{topic_name}/maxlatency", _{subname}_maxlatency)) {{
    ROS_ERROR("Subscription to Topic {topic_name} maximum latency is not provided (param ~/{topic_name}/maxlatency), setting it to 0 seconds");
    _{subname}_maxlatency = 0;
  }} */
  """
, 'pub_flags_fill'    : """// Set default flag for output {pubname}
    _out_flags.{pubname} = _gathered_flags;"""
, 'in_flags_struct_def'  : "radl_flags_t {subname};"
, 'out_flags_struct_def'  : "radl_flags_t {pubname};"
}

separators = {'msg_include'       : '\n'    , 'out_struct_def'    : '\n  ',
              'out_fill'          : '\n  '  , 'pub_call'          : '\n  ',
              'set_pub'           : '\n  '  , 'in_struct_def'     : '\n  ',
              'in_fill'           : '\n    ', 'init_msg_fill'     : '\n  ',
              'set_sub'           : '\n  '  , 'timeout_counters'  : '\n    ',
              'pub_flags_fill'    : '\n    ', 'in_flags_struct_def'  : '\n  ',
              'out_flags_struct_def'  : '\n  '}

def app(d, s):
    v = templates[s].format(**d)
    if s not in d or not d[s]: d[s] = v
    else: d[s] = separators[s].join((d[s], v))


def to_rate(node):
    if node == None:
        return "-1"
    else:
        return "1000000000.0/{}".format(node._val)

def to_ros_duration(node):
    return "ros::Duration().fromNSec({})".format(node._val)

def gennode(node):
    """ Nodes are not recursive for now """

    nodemodule = node._qname.rootmodule()
    node_is_C = node_sources_type(node) == 'C'

    d = {'in_struct_type'     : 'radl_in_t',
         'out_struct_type'    : 'radl_out_t',
         'in_flags_struct'    : 'radl_in_flags_t',
         'out_flags_struct'   : 'radl_out_flags_t',
         'node_module_init'   : qn.c_modinit(nodemodule),
         'node_module_header' : qn.file_ast(nodemodule, '.h'),
         'period'             : to_rate(node['PERIOD']), #TODO: 5 correct when ros is fixed and allow a duration as rate constructor argument
    }

    if infos.instrumentation:
        d['instruments_init'] = instrumentation.init_hook()
        d['instruments_start'] = instrumentation.step_start_hook()
        d['instruments_done'] = instrumentation.step_done_hook()
    else:
        d['instruments_init'] = ''
        d['instruments_start'] = ''
        d['instruments_done'] = ''


    init, step, finish = user_node_class(node, '_node',
                               '_pin', '_pin_flags', '&_out', '&_out_flags')
    d['node_state_init'] = init
    d['node_step_call'] = step
    d['node_state_finish'] = finish

    d['include_user_header'] = '#include "' + node_user_header_file(node) + '"'
    if node_is_C:
        d['include_user_header'] = 'extern "C" {\n'+d['include_user_header']+'\n}'


    #Over publications and subscriptions
    pubsub_templates = ['msg_include']
    for pt in pubsub_templates: d[pt] = ''
    #Over the publications
    pub_templates = ['pub_call', 'out_fill' , 'set_pub', 'out_flags_struct_def',
                     'out_struct_def', 'pub_flags_fill']
    for pt in pub_templates: d[pt] = ''
    for pub in node['PUBLISHES']:
        topic = pub['TOPIC']
        d.update({'pubname'     : pub._name,
                  'topic_name'  : qn_topic(topic._qname),
                  'actionname'  : '_' + pub._name + '_pub',
                  'topic_file'  : topic._ros_msgtype_header,
                  'topic_t'     : topic._ros_msgtype_name,
                  'initmsg'     : '_init_' + pub._name})

        #Select correct action definition
        each = pub['EACH']
        if each:
            d['each'] = each._val
            d['actiondef'] = 'radl::Default_pub_each<{topic_t}> {actionname}(*{actionname}_ros, {each});'.format(**d)
        else:
            d['actiondef'] = 'radl::Default_pub<{topic_t}> {actionname}(*{actionname}_ros);'.format(**d)

        init_stmts = copy_to(d['initmsg'], topic, init=True)
        d['init_msg_fill'] = separators['init_msg_fill'].join(init_stmts)
        if infos.instrument_msg_timings:
            d['pub_hooks'] = msg_timings.msg_pub_hook(
                topic._qname, pub._name, '_out.' + d['pubname'])
        else:
            d['pub_hooks'] = ''
        for f in pub_templates: app(d, f)
        for f in pubsub_templates: app(d, f)

    #Over the subscriptions
    sub_templates = ['in_fill', 'set_sub', 'in_struct_def', 'in_flags_struct_def',
                     'timeout_counters']
    for init in sub_templates: d[init] = ''
    for sub in node['SUBSCRIBES']:
        topic = sub['TOPIC']
        d.update({'subname'     : sub._name,
                  'topic_name'  : qn_topic(topic._qname),
                  'actionname'  : '_' + sub._name + '_sub',
                  'actionclass' : 'radl::Default_sub',
                  'topic_file'  : topic._ros_msgtype_header,
                  'topic_t'     : topic._ros_msgtype_name,
                  'initmsg'     : '_init_' + sub._name,
                  })

# The computation of max stale step is now done in the generated code
#        maxlatency = int(sub['MAXLATENCY']._val)
#        subspub = pub_node(topic)
#        if subspub is None:
#            warning("By lack of known publisher, subscription\n{}\nwill "
#                    "compute timeout assuming the publisher period is 100msec."
#                    "".format(str(sub._qname)), sub._location)
#            pub_period = 100000000
#            pub_wcet = None
#            pub_each = 1
#        else:
#            pub_period = int(subspub['PERIOD']._val)
#            pub_wcet = int(subspub['WCET']._val) if subspub['WCET'] else None
#            #TODO 8: This is makes the thing quadratic in worst case (look for the publication from the subscriber)...
#            pub_each = next((int(publi['EACH']._val) if publi['EACH'] else 1
#                             for publi in subspub['PUBLISHES']
#                             if publi['TOPIC']._qname == topic._qname), 1)
#        sub_period = int(node['PERIOD']._val)
#        d['mss'] = max_stale_steps(pub_period, maxlatency, sub_period,
#                                   pub_each, pub_wcet)

        init_stmts = copy_to('(*' + d['initmsg'] + ')', topic, init=True)
        d['init_msg_fill'] = separators['init_msg_fill'].join(init_stmts)

        if infos.instrument_msg_timings:
            d['sub_hooks'] = msg_timings.msg_sub_hook(
                topic._qname, node._qname, sub._name, '_in.' + d['subname'])
        else:
            d['sub_hooks'] = ''

        for f in sub_templates: app(d, f)
        for f in pubsub_templates: app(d, f)
    #generate the header file
    qname = node._qname
    d['name'] = qname.name()
    node_h_name = qn_srcfile(node._qname, 'radl__', '.h')
    node_h = templates['node_h'].format(**d)
    write_file(node_h_name, node_h)
    #generate the cpp file
    node_cpp_name = qn_srcfile(node._qname, 'radl__', '.cpp')
    node_cpp = templates['node_cpp'].format(
        node_h_name=node_h_name.name, rate=node['PERIOD']._val, node=node, **d)
    write_file(node_cpp_name, node_cpp)

    return node_h_name, node_cpp_name



#TODO Ros subscriber initialization is using a "new" to put in ConstPtr instead of just a shared pointer creation
