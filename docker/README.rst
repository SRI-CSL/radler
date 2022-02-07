To build the radler/ros2 docker image::

  docker build -t radler/ros2 .
  
To test pubsub example::

  docker run --rm -i -t radler/ros2:latest talker 
  docker run --rm -i -t radler/ros2:latest listener

You should see the output of the two nodes explaining that they are communicating. For more details see `pubsub` example documentation. 

You can stop everything by typing Ctrl-C.

To try SROS2 (https://github.com/ros2/sros2/blob/foxy/SROS2_Linux.md), start a container for both talker and listener nodes::

  docker run --env-file sros_env.list --rm -i -t radler/ros2:latest bash

Inside of the container, run listener and talker nodes with security feature on::

  ros2 run demo_nodes_py listener --ros-args --enclave /talker_listener/listener
  ros2 run demo_nodes_py talker --ros-args --enclave /talker_listener/talker

To run the above talker_listener demo on two containers, start one container c1::

  docker run --env-file sros_env.list --rm -i -t radler/ros2:latest bash

Inside of the container c1, prepare talker keys for SROS2 authentication and encryption::

  tar zchvf talker.tgz sros2_keys/enclaves/talker_listener/talker

Start another container c2::

  docker run --env-file sros_env.list --rm -i -t radler/ros2:latest bash

Copy talker keys from the container c1 to the container c2::

  docker ps
  docker cp c1_CONTAINER_ID:/root/talker.tgz .
  docker cp talker.tgz c2_CONTAINER_ID:/root/

Inside of the container c2, untar talker keys and run talker node::

  tar zxvf talker.tgz
  ros2 run demo_nodes_py talker --ros-args --enclave /talker_listener/talker

Inside of the container c1, run listener node::

  ros2 run demo_nodes_py listener --ros-args --enclave /talker_listener/listener
