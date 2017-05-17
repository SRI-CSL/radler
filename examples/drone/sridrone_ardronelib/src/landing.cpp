#include "ros/ros.h"
#include "landing.h"
#include <iostream>
#include <unistd.h>

using namespace std; 

void Landing::step(const radl_in_t * in, const radl_in_flags_t* iflags,
               radl_out_t * out, radl_out_flags_t* oflags) 
{
    double altitude = in->navdata->altitude;

	if ( *RADL_THIS->check_iflags ) {
        if ( radl_is_stale(iflags->navdata) )
            cout << "navdata is stale" << endl;
        if ( radl_is_timeout(iflags->navdata) )
            cout << "navdata is timeout" << endl;
    }

	if (altitude < 500 && altitude > 0) { 
		if ( *RADL_THIS->print_data ) {
            cout << "altitude = " << altitude << endl;
		}

		out->landing_event->nearground = true;
	}
	else 
		out->landing_event->nearground = false;
}
