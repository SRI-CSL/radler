#!/bin/bash
set -e

source  "$ROS2_PREFIX/$ROS2_DISTRO/setup.bash"

# radler  
cd ~/radler 
git pull

# ros4healthcare 
# fixes to commit hash 3b7ae0de19a319a39fd0299c577fd1e239d4535d
cd /root/ros2_ws/src/ros4healthcare/ros_healthcare_msg
sed -i '4s/ros2_hc_msgs/ros_healthcare_msg/' package.xml
sed -i '2s/ros2_hc_msgs/ros_healthcare_msg/' CMakeLists.txt 
mkdir /tmp/runtime-root 
chmod +x /tmp/runtime-root
cd /root/ros2_ws/src/ros4healthcare/ros2_hc_examples/applications/healthcare_wheelchair_dashboard/dashboard/src/dashboard/
sed -i '287s/msg.hr\[0\]/msg.hr/' interface_widget.py
sed -i '290s/msg.hr\[0\]/msg.hr/' interface_widget.py
sed -i '293s/msg.rr\[0\]/msg.rr/' interface_widget.py
cd ~/ros2_ws
colcon build --symlink-install
source install/setup.bash
xhost +localhost

exec "$@"
