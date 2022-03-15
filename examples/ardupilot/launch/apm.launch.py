import os
import sys

import launch
import launch_ros.actions
from ament_index_python.packages import get_package_share_directory


def generate_launch_description():
    ld = launch.LaunchDescription([
        launch.actions.DeclareLaunchArgument(
            name='fcu_url',
            default_value='udp://127.0.0.1:14550@'
        ),
        launch.actions.DeclareLaunchArgument(
            name='gcs_url',
            default_value='udp://@'
        ),
        launch.actions.DeclareLaunchArgument(
            name='tgt_system',
            default_value='1'
        ),
        launch.actions.DeclareLaunchArgument(
            name='tgt_component',
            default_value='1'
        ),
        launch.actions.DeclareLaunchArgument(
            name='log_output',
            default_value='screen'
        ),
        launch.actions.DeclareLaunchArgument(
            name='fcu_protocol',
            default_value='v2.0'
        ),
        launch.actions.DeclareLaunchArgument(
            name='respawn_mavros',
            default_value='false'
        ),
        launch.actions.IncludeLaunchDescription(
            launch.launch_description_sources.PythonLaunchDescriptionSource(
                os.path.join(get_package_share_directory(
                    'mavros'), 'launch/node.launch.py')
            ),
            launch_arguments={
                'plugin_mavros_yaml': get_package_share_directory('mavros') + '/launch/plugin_mavros.yaml',
                'plugin_global_position_yaml': get_package_share_directory('mavros') + '/launch/plugin_global_position.yaml',
                'plugin_setpoint_position_yaml': get_package_share_directory('mavros') + '/launch/plugin_setpoint_position.yaml',
                'plugin_sys_time_yaml': get_package_share_directory('mavros') + '/launch/plugin_sys_time.yaml',
                'plugin_sys_status_yaml': get_package_share_directory('mavros') + '/launch/plugin_sys_status.yaml',
                'plugin_imu_yaml': get_package_share_directory('mavros') + '/launch/plugin_imu.yaml',
                'plugin_cmd_yaml': get_package_share_directory('mavros') + '/launch/plugin_cmd.yaml',
                'mavros_config_yaml': get_package_share_directory('mavros') + '/launch/mavros_config.yaml',
                'global_position_config_yaml': get_package_share_directory('mavros') + '/launch/global_position_config.yaml',
                'setpoint_position_config_yaml': get_package_share_directory('mavros') + '/launch/setpoint_position_config.yaml',
                'sys_time_config_yaml': get_package_share_directory('mavros') + '/launch/sys_time_config.yaml',
                'sys_status_config_yaml': get_package_share_directory('mavros') + '/launch/sys_status_config.yaml',
                'imu_config_yaml': get_package_share_directory('mavros') + '/launch/imu_config.yaml',
                'cmd_config_yaml': get_package_share_directory('mavros') + '/launch/cmd_config.yaml',
                'fcu_url': launch.substitutions.LaunchConfiguration('fcu_url'),
                'gcs_url': launch.substitutions.LaunchConfiguration('gcs_url'),
                'tgt_system': launch.substitutions.LaunchConfiguration('tgt_system'),
                'tgt_component': launch.substitutions.LaunchConfiguration('tgt_component'),
                'log_output': launch.substitutions.LaunchConfiguration('log_output'),
                'fcu_protocol': launch.substitutions.LaunchConfiguration('fcu_protocol'),
                'respawn_mavros': launch.substitutions.LaunchConfiguration('respawn_mavros')
            }.items()
        )
    ])
    return ld


if __name__ == '__main__':
    generate_launch_description()
