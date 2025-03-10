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
  xterm -e "ros2 run healthcare hr_sensor" &    # execute radler nodes, e.g., hr_sensor
  ros2 run dashboard dashboard                  # execute ros4health dashboard 

Troubleshooting 
---------------

**Error Message:**

xhost: unable to open display "host.docker.internal:0"

**Steps to Fix:**

  1. Open Xquartz settings, go to the Security tab
  2. Make sure “Authenticate connections” is unchecked and “Allow connections from network clients” is checked
  3. Restart Xquartz
