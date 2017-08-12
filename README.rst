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

To get Radler working on a clean version of Ubuntu 14.04::

	sudo apt-get install cmake python3-pip
	sudo pip3 install tarjan pyyaml

To install ROS:: 

	sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu trusty main" > /etc/apt/sources.list.d/ros-latest.list'
	wget https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -O - | sudo apt-key add -
	sudo apt-get update
	sudo apt-get install ros-indigo-ros-base
	(echo ; echo "# Setup for ROS" ; echo "source /opt/ros/indigo/setup.bash" ) >> ~/.bashrc
	source ~/.bashrc


To compile and run  
----------------------------

Compile
~~~~~~~~
Radler generates files from the RADL file into a usual ROS catkin structure, then a call to `catkin_make` will generate the executables as usual.
(e.g., see  `examples/pubsub/pubsub.radl`)::

	mkdir -p /tmp/catkin_ws/src
	./radler.sh --ws_dir /tmp/catkin_ws/src compile examples/pubsub/single_machine/pubsub.radl --plant plant --ROS
	cd /tmp/catkin_ws
	catkin_make

Run
~~~~

Since `pubsub` defines a plant, Radler has generated a launch file to run the requested nodes.
The simplest way of running it is to source the catkin workspace we just compiled and use `roslaunch`::

    source devel/setup.bash
    roslaunch pubsub pubsub.plant.host_computer.launch

You should see the output of the two nodes explaining that they are communicating. For more details see `pubsub` example documentation. 

You can stop everything by typing Ctrl-C.

