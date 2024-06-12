cd ~/ros2_ws
ros2 security create_keystore sros2_keys
ros2 security create_key sros2_keys /afs/mavros
ros2 security create_key sros2_keys /afs/gateway
ros2 security create_key sros2_keys /afs/afs_battery
ros2 security create_key sros2_keys /afs/afs_esp
ros2 security create_key sros2_keys /afs/afs_log
