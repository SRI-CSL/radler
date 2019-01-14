Pubsub  
=======

This simple examples demonstrate how to write pubsub on single/multi machine. 

To generate the files from the .radl description, do:

::

   mkdir -p /tmp/ros2_ws/src
   cd /path/to/radler
   ./radler.sh --ws_dir /tmp/ros2_ws/src compile examples/pubsub/single_machine/pubsub.radl --plant plant --ROS
   cd /tmp/ros2_ws
   colcon build

You can then run all of them (in different terminals for more clarity):

:: 

   source install/local_setup.bash
   ./install/pubsub/bin/listener
   ./install/pubsub/bin/talker

For multi\_machine testing, use a different .radl file with modified plant section to list IPs for each machine in multi_machine directory as below:

:: 

  ./radler.sh --ws_dir=/tmp/ros2_ws/src compile examples/pubsub/multi_machine/pubsub.radl --plant plant --ROS

On machine 1: 

:: 

   source install/local_setup.bash
   ./install/pubsub/bin/talker 

On machine 2:

:: 
   
   source install/local_setup.bash
   ./install/pubsub/bin/listener 
