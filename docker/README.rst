To build the radler/ros2 docker image::

  docker build -t radler/ros2 .
  
To test pubsub example::

  docker run --rm -i -t radler/ros2:latest talker 
  docker run --rm -i -t radler/ros2:latest listener

You should see the output of the two nodes explaining that they are communicating. For more details see `pubsub` example documentation. 

You can stop everything by typing Ctrl-C.

