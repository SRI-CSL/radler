The Example of Room Temperature Regulation
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. container:: figure*

   .. image:: house_thermo_node_topic.png
      :scale: 10
      :height: 50
      :alt: image

Five nodes (in ellipse) communicate through six topics (in rectangle).
The ``button`` node publishes to ``thermostat_button`` and
``thermostat_set`` topics to generate signals that control the behavior
of thermostat by means of switching on/off and setting the target
temperature, respectively. The ``thermostat`` node subscribes from
``thermostat_button``, ``thermostat_set``, ``thermometer_data`` topics
and publishes to ``thermostat_data`` topic to regulate a room
temperature within min/max. The ``thermometer`` node subscribes from
``house_data`` topic and publishes to ``heater_data`` topic to measure
the room temperature with sensing noise. The ``heater`` node is the
actuator that subscribes from ``thermostat_data`` and publishes to
``heater_data``. The ``house`` node provides the physical room
temperature by subscribing from ``heater_data`` and publishing to
``house_data`` while the ``thermometer`` node provides the digital
sampled sensed temperature. A system consisting of these nodes was
defined in a RADL description with user code in each step function. The
Radler build process generates the glue code for scheduling,
communications, and failure detections for executables.

At the logical level, there are two main value types; node and topic.
Excerpt from the example system’s RADL description below:

::

   basic_rate : duration 50msec

     thermometer_data : topic { FIELDS temp : float32 75 }
     thermostat_button : topic { FIELDS status : bool true }
     thermostat_set : topic { FIELDS temp : float32 75 }

     thermostat_data : topic { FIELDS switch_on : bool true }

     thermostat : node {
       SUBSCRIBES
         thermometer_temp { TOPIC thermometer_data MAXLATENCY 1msec }
         thermostat_switch { TOPIC thermostat_button MAXLATENCY 1msec }
         thermostat_set_temp { TOPIC thermostat_set MAXLATENCY 1msec }
       PUBLISHES
         heater_switch { TOPIC thermostat_data }
       PATH "src"
       CXX
         { HEADER "thermostat.h" FILENAME "thermostat.cpp" CLASS "Thermostat" }
       PERIOD basic_rate
     }

A node is described with fields such as ``PERIOD``, ``PUBLISHES``, and
``SUBSCRIBES``. When the ``thermostat`` node is created, Radler
constructs one instance of the provided C++ class specified in the
``CXX`` field. The step function of this instance will be called at a
fixed frequency defined by the node’s period (the ``PERIOD`` field). At
each call, the step function is provided with the messages received from
its subscriptions and is required to write the messages that it has to
publish (the ``SUBSCRIBES`` and ``PUBLISHES`` fields). A topic is
uniquely defined by its name. For example, ``thermometer_data``,
``thermostat_button``, ``thermostat_set`` topics are referenced as
``thermometer_temp``, ``thermostat_switch``, ``thermostat_set_temp``,
respectively. The ``thermostat`` node publishes to the
``thermostat_data`` topic referenced as ``heater_switch`` and ``heater``
node subscribes from it. A topic is a purely logical way of defining
point-to-point communications between one producer and multiple
consumers. That is, there can be exactly one node publishing to a topic
(e.g., ``house_data``) while many nodes (e.g., ``thermometer_1`` ...
``thermometer_n`` in case of multiple sensors) can subscribe from it.
The communication occurs via bounded latency channel (the ``MAXLATENCY``
field) for each topic.

Below code segment shows the step function of the ``thermostat`` node,
that is provided by the user (C++ class specified in the ``CXX`` field
under the directory specified in the ``PATH`` field, as being
exemplified in the RADL description above).

::

   void Thermostat::step(const radl_in_t* in, const radl_in_flags_t* inflags,
                           radl_out_t* out, radl_out_flags_t* outflags)
     {
       // change the set temperature 
       this->set_temp = in->thermostat_set_temp->temp;

       // set the status
       this->status = in->thermostat_switch->status;

       // decide whether to switch on the heater
       if (in->thermometer_temp->temp > (this->set_temp + this->tol)) {
         out->heater_switch->switch_on = false;
       } else if (this->status && (in->thermometer_temp->temp < this->set_temp)) {
         out->heater_switch->switch_on = true;
       } else {
         out->heater_switch->switch_on = this->status;
       } 
     }

A class will be instantiated with the default constructor to generate an
instance representing the state of the Mealy machine. Subsequently, the
step function of this instance will be called to execute one step of the
machine. The signature of the step function should specify the input
(``radl_in_t*``) and output (``radl_out_t*``) structures define the
node’s subscription and publication, respectively. In the example, the
step function of the ``thermostat`` node regulates the room temperature
by switching on/off state of the heater. The flag structures
(``radl_inflags_t*, radl_outflags_t*``) can be used to check if a
subscription, e.g., ``thermometer_temp``, is stale or timeout by calling
``radl_is_stale(iflag->thermometer_temp)`` or
``radl _is_timeout(iflag->thermometer_temp)``, respectively. These
Boolean metadata attached to messages are by default propagate through
nodes unless the explicitly being turned off (``radl_turn_off``).

A physical specification is provided by a value of type plant:

::

   sys1 : linux {
       IP 192.168.1.201
       NODES heater
     }

     sys2 : linux {
       IP 192.168.1.202
       NODES thermostat
     }

     sys3 : linux {
       IP 192.168.1.203
       NODES thermometer house buttons
     }

     plant : plant {
       MACHINES
         house_heater { OS sys1 }
         house_computer { 
           OS l1 : lynxsecure {
             VMS
               vm1 { OS sys2 }
               vm2 { OS sys3 }
           }
         }
     }

The ``MACHINES`` field lists the machines that will be used by the
system. In the example, three machines are defined by the operating
system that it runs (the ``OS`` field). The ``IP`` and ``NODES`` fields
specify the IP address assigned for the OS and the nodes that run on the
OS. In the example, three nodes (i.e., ``thermometer``, ``house``,
``buttons``) run on the Linux with IP address of ``192.168.1.203`` while
``heater`` and ``thermostat`` nodes run on a separate Linux machine.
