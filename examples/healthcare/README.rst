To test with Docker 
-------------------

To build and run the radler/healthcare docker container::

  docker build -t radler/healthcare .
  docker run -it -e DISPLAY=host.docker.internal:0 radler/healthcare bash

Within the container::

  cd ~/radler/
  ./radler.sh --ws_dir /tmp/ros2_ws/src compile examples/healthcare/healthcare.radl --plant plant --ROS
  cd /tmp/ros2_ws/
  colcon build
  source install/local_setup.bash
  xterm -e "ros2 run healthcare gateway" &      # execute radler gateway  
  xterm -e "ros2 run healthcare hr_sensor" &    # execute radler nodes
  ros2 run dashboard dashboard                  # execute ros4health dashboard 
