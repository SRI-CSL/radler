#include "ros/ros.h"
#include "timer.h"
#include <iostream>
#include <unistd.h>

using namespace std; 

void Timer::step(const radl_in_t * in, const radl_in_flags_t* iflags,
               radl_out_t * out, radl_out_flags_t* oflags) 
{
        double altitude = in->navdata->altitude;

        if (altitude <= 0) { 	
		out->timer_event->expiry = false;
	}
	else { 
		sleep(2); 
	
		if ( *RADL_THIS->print_data ) {
        		cout << "timer expiry" << endl;
		}

		out->timer_event->expiry = true;
	}
}
