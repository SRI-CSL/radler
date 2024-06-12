#include "ros/ros.h"
#include "controller.h"
#include "std_msgs/String.h"
#include <iostream>
#include <string> 
#include <sys/stat.h>

using namespace std;

Controller::Controller()
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

	speaker_pub = nh.advertise<std_msgs::String>("/speaker_control", 10);
        if(!speaker_pub)
                std::cout << "ERROR:: publish to /speaker_control failed" << std::endl;
}

void Controller::step(const radl_in_t * in, const radl_in_flags_t* iflags,
               radl_out_t * out, radl_out_flags_t* oflags) 
{
	int x=-1,y=-1,width=1,height=1; 
	double volume=0.0; 

	double lat=0.0, lon=0.0; 
	int azimuth=0; 

	// compass
	azimuth = in->compass_status->azimuth; 
	
	// gps
	lat = in->gps_status->lat;
	lon = in->gps_status->lon;
	
	// touch 
	x = in->touch_status->x;
	y = in->touch_status->y;
	width = in->touch_status->width;
	height = in->touch_status->height;

	// volume 
	volume = (double) x / (double) width;
	if (volume > 1) volume = 1.0;
	if (volume < 0) volume = 0.0;
	if (isnan(volume)) volume = 0.0;

	std_msgs::String msg; 
	std::stringstream ss;
       	ss << volume;
       	msg.data = ss.str();
	speaker_pub.publish(msg); 

	if ( *RADL_THIS->print_data ) {
		cout << "control node compass " << azimuth << endl;
		cout << "                 gps " << lat << ":" << lon << endl;
       		cout << "               touch " << x << ":" << y << ":" << width << ":" << height << endl;
       		cout << "              volume " << volume << endl;
	}
}
