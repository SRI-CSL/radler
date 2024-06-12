#include "ros/ros.h"
#include "detector.h"
#include <iostream>

using namespace std;

Detector::Detector()
{
    	cout << "Set ROS environment" << endl;

	string command;
	command = string( "export ROS_IP=" ) + *RADL_THIS->android_ip;
	system( command.c_str() );
	command = string( "export ROS_HOSTNAME=" ) + *RADL_THIS->android_ip;
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
}

void Detector::step(const radl_in_t * in, const radl_in_flags_t* iflags,
               radl_out_t * out, radl_out_flags_t* oflags) 
{
       	cout << ((in->ts_status->on == true) ? "O" : "		X") << endl;
}
