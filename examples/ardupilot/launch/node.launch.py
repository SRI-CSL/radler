import os
import sys

import launch
import launch_ros.actions
from launch_ros.actions import Node

def generate_launch_description():
    ld = launch.LaunchDescription([
        launch.actions.DeclareLaunchArgument(
            name='fcu_url'
        ),
        launch.actions.DeclareLaunchArgument(
            name='gcs_url'
        ),
        launch.actions.DeclareLaunchArgument(
            name='tgt_system'
        ),
        launch.actions.DeclareLaunchArgument(
            name='tgt_component'
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
        )
    ])

    mavros_node = Node(
        package='mavros',
        executable='mavros_node',
        name='mavros',
        #output=launch.substitutions.LaunchConfiguration('log_output'),
        parameters=[
            {
                'fcu_url': launch.substitutions.LaunchConfiguration('fcu_url')
            },
            {
                'gcs_url': launch.substitutions.LaunchConfiguration('gcs_url')
            },
            {
                'target_system_id': launch.substitutions.LaunchConfiguration('tgt_system')
            },
            {
                'target_component_id': launch.substitutions.LaunchConfiguration('tgt_component')
            },
            {
                'fcu_protocol': launch.substitutions.LaunchConfiguration('fcu_protocol')
            },
            launch.substitutions.LaunchConfiguration('plugin_mavros_yaml'),
            launch.substitutions.LaunchConfiguration('mavros_config_yaml')
        ]
    )
    global_position_node = Node(
        package='mavros',
        executable='mavros_node',
        namespace='mavros',
        name='global_position',
        #output=launch.substitutions.LaunchConfiguration('log_output'),
        parameters=[
            {
                'fcu_url': launch.substitutions.LaunchConfiguration('fcu_url')
            },
            {
                'gcs_url': launch.substitutions.LaunchConfiguration('gcs_url')
            },
            {
                'target_system_id': launch.substitutions.LaunchConfiguration('tgt_system')
            },
            {
                'target_component_id': launch.substitutions.LaunchConfiguration('tgt_component')
            },
            {
                'fcu_protocol': launch.substitutions.LaunchConfiguration('fcu_protocol')
            },
            launch.substitutions.LaunchConfiguration('plugin_global_position_yaml'),
            launch.substitutions.LaunchConfiguration('global_position_config_yaml')
        ]
    )
    sys_time_node = Node(
        package='mavros',
        executable='mavros_node',
        namespace='mavros',
        name='sys_time',
        #output=launch.substitutions.LaunchConfiguration('log_output'),
        parameters=[
            {
                'fcu_url': launch.substitutions.LaunchConfiguration('fcu_url')
            },
            {
                'gcs_url': launch.substitutions.LaunchConfiguration('gcs_url')
            },
            {
                'target_system_id': launch.substitutions.LaunchConfiguration('tgt_system')
            },
            {
                'target_component_id': launch.substitutions.LaunchConfiguration('tgt_component')
            },
            {
                'fcu_protocol': launch.substitutions.LaunchConfiguration('fcu_protocol')
            },
            launch.substitutions.LaunchConfiguration('plugin_sys_time_yaml'),
            launch.substitutions.LaunchConfiguration('sys_time_config_yaml')
        ]
    )
    sys_status_node = Node(
        package='mavros',
        executable='mavros_node',
        namespace='mavros',
        name='sys_status',
        #output=launch.substitutions.LaunchConfiguration('log_output'),
        parameters=[
            {
                'fcu_url': launch.substitutions.LaunchConfiguration('fcu_url')
            },
            {
                'gcs_url': launch.substitutions.LaunchConfiguration('gcs_url')
            },
            {
                'target_system_id': launch.substitutions.LaunchConfiguration('tgt_system')
            },
            {
                'target_component_id': launch.substitutions.LaunchConfiguration('tgt_component')
            },
            {
                'fcu_protocol': launch.substitutions.LaunchConfiguration('fcu_protocol')
            },
            launch.substitutions.LaunchConfiguration('plugin_sys_status_yaml'),
            launch.substitutions.LaunchConfiguration('sys_status_config_yaml')
        ]
    )
    imu_node = Node(
        package='mavros',
        executable='mavros_node',
        namespace='mavros',
        name='imu',
        #output=launch.substitutions.LaunchConfiguration('log_output'),
        parameters=[
            {
                'fcu_url': launch.substitutions.LaunchConfiguration('fcu_url')
            },
            {
                'gcs_url': launch.substitutions.LaunchConfiguration('gcs_url')
            },
            {
                'target_system_id': launch.substitutions.LaunchConfiguration('tgt_system')
            },
            {
                'target_component_id': launch.substitutions.LaunchConfiguration('tgt_component')
            },
            {
                'fcu_protocol': launch.substitutions.LaunchConfiguration('fcu_protocol')
            },
            launch.substitutions.LaunchConfiguration('plugin_imu_yaml'),
            launch.substitutions.LaunchConfiguration('imu_config_yaml')
        ]
    )
    cmd_node = Node(
        package='mavros',
        executable='mavros_node',
        namespace='mavros',
        name='cmd',
        #output=launch.substitutions.LaunchConfiguration('log_output'),
        parameters=[
            {
                'fcu_url': launch.substitutions.LaunchConfiguration('fcu_url')
            },
            {
                'gcs_url': launch.substitutions.LaunchConfiguration('gcs_url')
            },
            {
                'target_system_id': launch.substitutions.LaunchConfiguration('tgt_system')
            },
            {
                'target_component_id': launch.substitutions.LaunchConfiguration('tgt_component')
            },
            {
                'fcu_protocol': launch.substitutions.LaunchConfiguration('fcu_protocol')
            },
            launch.substitutions.LaunchConfiguration('plugin_cmd_yaml'),
            launch.substitutions.LaunchConfiguration('cmd_config_yaml')
        ]
    )

    ld.add_action(mavros_node)
    ld.add_action(global_position_node)
    ld.add_action(sys_time_node)
    ld.add_action(sys_status_node)
    ld.add_action(imu_node)
    ld.add_action(cmd_node)
    return ld


if __name__ == '__main__':
    generate_launch_description()
