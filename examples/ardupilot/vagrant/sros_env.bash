export ROS_SECURITY_KEYSTORE=/home/vagrant/ros2_ws/sros2_keys
export ROS_SECURITY_ENABLE=true
export ROS_SECURITY_STRATEGY=Enforce
export RMW_IMPLEMENTATION=rmw_fastrtps_cpp

mkdir -p ~/ros2_ws/install/afs/lib/afs
cd ~/ros2_ws/install/afs/lib/afs
ln -sf ../../../../build/afs/gateway .
ln -sf ../../../../build/afs/afs_battery .
ln -sf ../../../../build/afs/afs_esp .
ln -sf ../../../../build/afs/afs_log .
