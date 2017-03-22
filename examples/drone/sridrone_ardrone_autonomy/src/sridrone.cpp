#include "ros/ros.h"
#include "sridrone.h"
#include <ardrone_autonomy/Navdata.h>

#include <iostream>

ardrone_autonomy::Navdata lastNavdataReceived; 

void navdataCb(const ardrone_autonomy::NavdataConstPtr navdataPtr) {
	lastNavdataReceived = *navdataPtr;
}

SRIDrone::SRIDrone()
{
	navdata_sub = nh.subscribe<ardrone_autonomy::Navdata>("/ardrone/navdata", 10, navdataCb); 
        if(!navdata_sub)
                std::cout << "ERROR:: subscribe to /ardrone/navdata failed" << std::endl;
}

void SRIDrone::step(const radl_in_t * in, const radl_in_flags_t* iflags,
                 radl_out_t * out, radl_out_flags_t * oflags) 
{
        std::cout << "-----------------------------------" << std::endl;

        // Orientation
        double roll  = lastNavdataReceived.rotX;
        double pitch = lastNavdataReceived.rotY;
        double yaw   = lastNavdataReceived.rotZ;

        // Altitude
        double altitude = lastNavdataReceived.altd;

        // Velocity
	double v_x = lastNavdataReceived.vx; 
	double v_y = lastNavdataReceived.vy; 
	double v_z = lastNavdataReceived.vz; 

        // Battery
        int battery = lastNavdataReceived.batteryPercent;

        out->navdata->roll = roll;
        out->navdata->pitch = pitch;
        out->navdata->yaw = yaw;

        out->navdata->altitude = altitude;
        out->navdata->vx = v_x;
        out->navdata->vy = v_y;
        out->navdata->vz = v_z;

        out->navdata->battery = battery;

        std::cout << "ardrone.roll  = " << roll  << " [deg]" << std::endl;
        std::cout << "ardrone.pitch = " << pitch << " [deg]" << std::endl;
        std::cout << "ardrone.yaw   = " << yaw   << " [deg]" << std::endl;
        std::cout << "ardrone.altitude = " << altitude << " [m]" << std::endl;
        std::cout << "ardrone.vx = " << v_x << " [m/s]" << std::endl;
        std::cout << "ardrone.vy = " << v_y << " [m/s]" << std::endl;
        std::cout << "ardrone.vz = " << v_z << " [m/s]" << std::endl;
        std::cout << "ardrone.battery = " << battery << " [%]" << std::endl;
}
