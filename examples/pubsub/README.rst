Pub/Sub  
-------

This simple examples demonstrate how to write pub/sub on single/multi machine. 

To generate the files from the radl description, do:

::

   mkdir -p /tmp/catkin_ws/src
   cd /path/to/radler
   ./radler.sh --ws_dir=/tmp/catkin_ws/src compile examples/pubsub/single_machine/pubsub.radl --plant plant --ROS
   cd /tmp/catkin_ws
   catkin_make

You can then run all of them (in different terminals for more clarity):

:: 

   roscore
   ./devel/lib/pubsub/talker 
   ./devel/lib/pubsub/listener 

For multi\_machine testing, use a different .radl file in multi_machine directory as below:

:: 

   ./radler.sh --ws_dir=/tmp/catkin_ws/src compile examples/pubsub/multi_machine/pubsub.radl --plant plant --ROS

For running on multi\_machine setup, copy executables to the corresponding machines. Refer plant section of .radl file for the IPs as below.

:: 

   scp /tmp/catkin_ws/devel/lib/pubsub/talker 192.168.10.202:~
   scp /tmp/catkin_ws/devel/lib/pubsub/listener 192.168.10.203:~

On machine 192.168.10.201:

::

   roscore 

On machine 192.168.10.202:

:: 
   
   ./talker 

On machine 192.168.10.203:

:: 
   
   ./listener 
