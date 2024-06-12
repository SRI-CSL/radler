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
            default_value=''
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
                    'mavros'), 'launch/descert_node.launch.py')
            ),
            launch_arguments={
                'pluginlists_yaml': get_package_share_directory('mavros') + '/launch/descert_pluginlists.yaml',
                'config_yaml': get_package_share_directory('mavros') + '/launch/descert_config.yaml',
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
