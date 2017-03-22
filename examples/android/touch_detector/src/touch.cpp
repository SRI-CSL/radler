#include "ros/ros.h"
#include "touch.h"
#include <iostream>
#include <sys/stat.h>

using namespace std;

Touch::Touch()
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

void Touch::step(const radl_in_t * in, const radl_in_flags_t* iflags,
               radl_out_t * out, radl_out_flags_t* oflags) 
{
	string command;
	command = string( "timeout -t 1 getevent -c 1 /dev/input/event" ) + *RADL_THIS->ts_event + string ( " > ts 2&>/dev/null" );
	system( command.c_str() );

	struct stat filestatus;
        stat( "ts", &filestatus );

        if ( filestatus.st_size > 0 ) 
                out->ts_status->on = true; 
        else 
                out->ts_status->on = false; 

	if ( *RADL_THIS->print_data ) 
       		cout << ((out->ts_status->on == true) ? "O" : "		X") << endl;
}
