#!/bin/bash
set -e

# setup ros2 environment
source "$ROS2_PREFIX/$ROS2_DISTRO/setup.bash"

# build radler pubsub example
cd ~/radler 
git pull
./radler.sh --ws_dir $ROS2_WS/src compile examples/pubsub/multi_machine/pubsub.radl --plant plant --ROS
cd $ROS2_WS
colcon build \
    --cmake-args \
      -DSECURITY=ON --no-warn-unused-cli \
    --symlink-install
source "$ROS2_WS/install/local_setup.bash"

#sros2
cd ~
ros2 security create_keystore sros2_keys
ros2 security create_key sros2_keys /talker_listener/talker
ros2 security create_key sros2_keys /talker_listener/listener

exec "$@"
