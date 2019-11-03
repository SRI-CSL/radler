#!/bin/bash
set -e

# setup ros environment
source "$ROS_PREFIX/$ROS_DISTRO/setup.bash"
export ROS_IP=`hostname -i`

# build radler pubsub example
cd ~/radler 
git pull
./radler.sh --ws_dir $ROS_WS/src compile examples/pubsub/multi_machine/pubsub.radl --plant plant --ROS
cd $ROS_WS
catkin_make
source "$ROS_WS/devel/setup.bash"
exec "$@"
