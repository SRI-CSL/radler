import os
import sys

import launch
import launch_ros.actions


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
            name='pluginlists_yaml'
        ),
        launch.actions.DeclareLaunchArgument(
            name='config_yaml'
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
        launch_ros.actions.Node(
            package='mavros',
            executable='mavros_node',
            name='mavros',
            output='screen',
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
                launch.substitutions.LaunchConfiguration('pluginlists_yaml'),
                launch.substitutions.LaunchConfiguration('config_yaml')
            ]
        )
    ])
    return ld


if __name__ == '__main__':
    generate_launch_description()
