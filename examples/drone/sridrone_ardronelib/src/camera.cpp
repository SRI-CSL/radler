#include "ros/ros.h"
#include "camera.h"
#include <iostream>

extern "C" {
#include <ardrone_api.h>
#include <Maths/maths.h>
}

void Camera::step(const radl_in_t * in, const radl_in_flags_t* iflags,
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

        if ( (pitch > 30.0) || (pitch < -30.0) ) {
                out->camera_param->mode = 1;
                std::cout << "Bottom Camera" << std::endl;
        }
	else { 
                out->camera_param->mode = 0;
                std::cout << "Front Camera" << std::endl;
	} 
}
