#include "ros/ros.h"
#include "camera.h"
#include <std_srvs/Empty.h>
#include <ardrone_autonomy/CamSelect.h>

#include <iostream>

void Camera::step(const radl_in_t * in, const radl_in_flags_t* inflags,
                  radl_out_t * out, radl_out_flags_t* outflags) 
{
        double roll = in->navdata->roll;
        double pitch = in->navdata->pitch;
        double yaw = in->navdata->yaw;

        double altitude = in->navdata->altitude;
        double v_x = in->navdata->vx;
        double v_y = in->navdata->vy;
        double v_z = in->navdata->vz;

        int battery = in->navdata->battery;

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

        if ((pitch > 30.0) || (pitch < -30.0)) {
                out->camera_param->mode = 1;
                std::cout << "Bottom Camera" << std::endl;
        }
	      else { 
                out->camera_param->mode = 0;
                std::cout << "Front Camera" << std::endl;
	      } 

	      // ros::ServiceClient client = nh.serviceClient<std_srvs::Empty>("ardrone/togglecam");
        // std_srvs::Empty srv;
	
        ros::ServiceClient client = nh.serviceClient<ardrone_autonomy::CamSelect>("ardrone/setcamchannel");

        if(ros::ok()) {
                ardrone_autonomy::CamSelect srv;
                srv.request.channel = out->camera_param->mode;
                client.call(srv);
        }
}
