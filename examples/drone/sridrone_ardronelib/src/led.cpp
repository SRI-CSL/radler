#include "ros/ros.h"
#include "led.h"
#include <iostream>

using namespace std;

extern "C" {
#include <ardrone_api.h>
#include <Maths/maths.h>
}

void Led::step(const radl_in_t * in, const radl_in_flags_t* iflags,
               radl_out_t * out, radl_out_flags_t* oflags) 
{
    double roll = in->navdata->roll * RAD_TO_DEG;
    double pitch = in->navdata->pitch * RAD_TO_DEG;
    double yaw = in->navdata->yaw * RAD_TO_DEG;
    double altitude = in->navdata->altitude;
    double v_x = in->navdata->vx;
    double v_y = in->navdata->vy;
    double v_z = in->navdata->vz;
    int battery = in->navdata->battery;

	if ( *RADL_THIS->print_data ) {
        cout << "-----------------------------------" << endl;

        // Orientation
        cout << "ardrone.roll  = " << roll  << " [deg]" << endl;
        cout << "ardrone.pitch = " << pitch << " [deg]" << endl;
        cout << "ardrone.yaw   = " << yaw   << " [deg]" << endl;

        // Altitude
        cout << "ardrone.altitude = " << altitude << " [m]" << endl;

        // Velocity
        cout << "ardrone.vx = " << v_x << " [m/s]" << endl;
        cout << "ardrone.vy = " << v_y << " [m/s]" << endl;
        cout << "ardrone.vz = " << v_z << " [m/s]" << endl;

        // Battery
        cout << "ardrone.battery = " << battery << " [%]" << endl;
	}

	if ( *RADL_THIS->check_iflags ) {
		if ( radl_is_stale(iflags->navdata) ) 
			cout << "navdata is stale" << endl;
		if ( radl_is_timeout(iflags->navdata) ) 
			cout << "navdata is timeout" << endl;
	}

    if ( roll > 30.0 ) {
		out->led_anim->id = LEFT_GREEN_RIGHT_RED; 
		cout << "[Warning - Roll " << roll << " (>30.0)] ARDRONE_LED_ANIM_LEFT_GREEN_RIGHT_RED" << endl;
	}
    else if ( roll < -30.0 ) {
		out->led_anim->id = LEFT_RED_RIGHT_GREEN; 
		cout << "[Warning - Roll " << roll << " (<-30.0)] ARDRONE_LED_ANIM_LEFT_RED_RIGHT_GREEN" << endl;
	}
	else 
		out->led_anim->id = GREEN; 
		
	out->led_anim->freq = 4; 
	out->led_anim->span = 2; 

    cout << "LED sets ardrone.setAnimation = " << out->led_anim->id << endl;
}
