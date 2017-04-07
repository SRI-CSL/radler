Controller_Gateway   
==================

This example demonstrates how to write a gateway to forward back-and-forth messages between Radler world and a local sandboxed ROS.

Radler world is defined in the radl_files folder. It consists of .radl description containing three nodes. A device stub publishing an integer, an actuator stub subscribing to a float and a gateway node for an external controller node, forwarding device msgs to it and forwarding actuators msgs from it.

To complete the example, a stub of a sandboxed ROS controller node is also provided in the sandboxed_ros_controller folder.

There are basically two interesting files, the gateway.radl description of Radler system which defines the gateway node and the associated gateway.h file implementing the actual gateway.

To generate the files from .radl description, do:

::

    mkdir -p /tmp/catkin_ws/src
    cd /path/to/radler
    ./radler.sh --ws_dir /tmp/catkin_ws/src compile examples/controller_gateway/radl_files/gateway.radl --ROS 

Then to compile everything and get ROS executables, do:

:: 

   ln -s /path/to/radler/example/controller_gateway/sandboxed_ros_controller /tmp/catkin_ws/src
   cd /tmp/catkin_ws
   catkin_make

You can then run all of them (in different terminals for more clarity):

:: 

   roscore
   ./devel/lib/gateway/device_node
   ./devel/lib/gateway/actuator_node
   ./devel/lib/gateway/controller_gateway
   ./devel/lib/sandboxed_ros_controller/sandboxed_ros_controller_node 
