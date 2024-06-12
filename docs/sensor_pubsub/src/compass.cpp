#include "ros/ros.h"
#include "compass.h"
#include "std_msgs/String.h"
#include <iostream>
#include <sys/stat.h>

using namespace std;

std_msgs::String lastAzimuth; 

void compassCb(const std_msgs::String::ConstPtr& msg)
{
	lastAzimuth = *msg; 
}

Compass::Compass()
{
    	cout << "Set ROS environment" << endl;

	string command;
	command = string( "export ROS_IP=" ) + *RADL_THIS->master_ip;
	system( command.c_str() );
	command = string( "export ROS_HOSTNAME=" ) + *RADL_THIS->master_ip;
	system( command.c_str() );
	string( "export ROS_MASTER_URI=http://" ) + *RADL_THIS->master_ip + string ( ":11311" );
	system( command.c_str() );

	cout << "ROS_IP=";
	system("echo $ROS_IP");
	cout << endl << "ROS_HOSTNAME=";
	system("echo $ROS_HOSTNAME");
	cout << endl << "ROS_MASTER_URI=";
	system("echo $ROS_MASTER_URI");
	cout << endl;

        compass_sub = nh.subscribe<std_msgs::String>("android_compass", 10, compassCb);
        if(!compass_sub)
                std::cout << "ERROR:: subscribe to /android_compass failed" << std::endl;
}

void Compass::step(const radl_in_t * in, const radl_in_flags_t* iflags,
               radl_out_t * out, radl_out_flags_t* oflags) 
{
	int a; 
	sscanf (lastAzimuth.data.c_str(), "%d:", &a); 
	out->compass_status->azimuth = a;

	if ( *RADL_THIS->print_data ) 
       		cout << "compass_node: " << a << endl;
}
