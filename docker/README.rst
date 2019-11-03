To build the radler/ros docker image::

  docker build -t radler/ros .
  
To test pubsub example::

  docker run --rm -i -t radler/ros:latest roscore 
  docker run --rm -i -t radler/ros:latest devel/lib/pubsub/talker 
  docker run --rm -i -t radler/ros:latest devel/lib/pubsub/listener

You should see the output of the two nodes explaining that they are communicating. For more details see `pubsub` example documentation. 

You can stop everything by typing Ctrl-C.

