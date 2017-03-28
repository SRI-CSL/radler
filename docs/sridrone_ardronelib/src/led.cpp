#include "ros/ros.h"
#include "led.h"
#include <iostream>

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
        	std::cout << "-----------------------------------" << std::endl;

        	// Orientation
        	std::cout << "ardrone.roll  = " << roll  << " [deg]" << std::endl;
        	std::cout << "ardrone.pitch = " << pitch << " [deg]" << std::endl;
        	std::cout << "ardrone.yaw   = " << yaw   << " [deg]" << std::endl;

        	// Altitude
        	std::cout << "ardrone.altitude = " << altitude << " [m]" << std::endl;

        	// Velocity
        	std::cout << "ardrone.vx = " << v_x << " [m/s]" << std::endl;
        	std::cout << "ardrone.vy = " << v_y << " [m/s]" << std::endl;
        	std::cout << "ardrone.vz = " << v_z << " [m/s]" << std::endl;

        	// Battery
        	std::cout << "ardrone.battery = " << battery << " [%]" << std::endl;
	}

	if ( *RADL_THIS->check_iflags ) {
		if ( radl_is_stale(iflags->navdata) ) 
			std::cout << "navdata is stale" << std::endl;
		if ( radl_is_timeout(iflags->navdata) ) 
			std::cout << "navdata is timeout" << std::endl;
	}

        if ( roll > 30.0 ) {
		out->led_anim->id = LEFT_GREEN_RIGHT_RED; 
		std::cout << "[Warning - Roll " << roll << " (>30.0)] ARDRONE_LED_ANIM_LEFT_GREEN_RIGHT_RED" << std::endl;
	}
        else if ( roll < -30.0 ) {
		out->led_anim->id = LEFT_RED_RIGHT_GREEN; 
		std::cout << "[Warning - Roll " << roll << " (<-30.0)] ARDRONE_LED_ANIM_LEFT_RED_RIGHT_GREEN" << std::endl;
	}
	else 
		out->led_anim->id = GREEN; 
		
	out->led_anim->freq = 4; 
	out->led_anim->span = 2; 

        std::cout << "LED sets ardrone.setAnimation = " << out->led_anim->id << std::endl;
}
