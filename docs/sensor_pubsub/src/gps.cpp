#include "ros/ros.h"
#include "gps.h"
#include "std_msgs/String.h"
#include <iostream>
#include <sys/stat.h>

using namespace std;

std_msgs::String lastGPSCoordinates; 

void gpsCb(const std_msgs::String::ConstPtr& msg)
{
	lastGPSCoordinates = *msg; 
}

GPS::GPS()
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

        gps_sub = nh.subscribe<std_msgs::String>("android_gps", 10, gpsCb);
        if(!gps_sub)
                std::cout << "ERROR:: subscribe to /android_gps failed" << std::endl;
}

void GPS::step(const radl_in_t * in, const radl_in_flags_t* iflags,
               radl_out_t * out, radl_out_flags_t* oflags) 
{
	double lat,lon; 
	sscanf (lastGPSCoordinates.data.c_str(), "%lf:%lf", &lat, &lon); 
	out->gps_status->lat = lat;
	out->gps_status->lon = lon;
	if ( *RADL_THIS->print_data ) 
       		cout << "gps node: " << lat << ":" << lon << endl;
}
