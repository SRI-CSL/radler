Radler framework takes its inspiration from the Robot Operating System (ROS). In Radler framework, the sensors, controllers, and actuators are constructed from functional units called nodes. Each node executes independently with a period determined by a local clock and scheduling constraints. Radler supports a publish/subscribe architecture where nodes communicate by publishing on certain topics and subscribing to other topics.

Getting Started 
=============== 

Find the documentation at https://sri-csl.github.io/radler/

To install  
----------

To checkout repository::

    git clone https://github.com/SRI-CSL/radler.git
    cd radler
    git submodule update --init --recursive

To get Radler working on a clean version of Ubuntu 16.04::

	sudo apt-get install cmake python3-pip
	sudo pip3 install tarjan pyyaml

To install ROS2, follow the instructions from https://index.ros.org/doc/ros2/Installation/

To install colcon, follow the instructions from https://colcon.readthedocs.io/en/released/user/installation.html

To compile and run  
----------------------------

Compile
~~~~~~~~
Radler generates files from the RADL file into a usual ROS2 structure, then a call to `colcon build` will generate the executables as usual.
(e.g., see  `examples/pubsub/pubsub.radl`)::

	mkdir -p /tmp/ros2_ws/src
	./radler.sh --ws_dir /tmp/ros2_ws/src compile examples/pubsub/single_machine/pubsub.radl --plant plant --ROS
	cd /tmp/ros2_ws
	colcon build

Run
~~~~

The simplest way of running it is to source the ros2 workspace we just compiled and invoke it by name directly::

    source install/local_setup.bash
    ./install/pubsub/bin/listener
    ./install/pubsub/bin/talker

You should see the output of the two nodes explaining that they are communicating. For more details see `pubsub` example documentation. 

You can stop everything by typing Ctrl-C.

