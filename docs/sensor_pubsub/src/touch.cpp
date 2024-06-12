#include "ros/ros.h"
#include "touch.h"
#include "std_msgs/String.h"
#include <iostream>
#include <sys/stat.h>

using namespace std;

std_msgs::String lastTouchCoordinates; 

void touchCb(const std_msgs::String::ConstPtr& msg)
{
	lastTouchCoordinates = *msg; 
}

Touch::Touch()
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

        touch_sub = nh.subscribe<std_msgs::String>("android_touch", 10, touchCb);
        if(!touch_sub)
                std::cout << "ERROR:: subscribe to /android_touch failed" << std::endl;
}

void Touch::step(const radl_in_t * in, const radl_in_flags_t* iflags,
               radl_out_t * out, radl_out_flags_t* oflags) 
{
	int x,y,width,height; 
	sscanf (lastTouchCoordinates.data.c_str(), "%d:%d:%d:%d", &x, &y, &width, &height); 
	out->touch_status->x = x;
	out->touch_status->y = y;
	out->touch_status->width = width;
	out->touch_status->height = height; 

	if ( *RADL_THIS->print_data ) 
       		cout << "touch node: " << x << ":" << y << ":" << width << ":" << height << endl;
}
