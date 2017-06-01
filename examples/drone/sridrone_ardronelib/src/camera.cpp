

#include "ros/ros.h"
#include "camera.h"
#include <iostream>

using namespace std;

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

    if ( (pitch > 30.0) || (pitch < -30.0) ) {
        out->camera_param->mode = 1;
        cout << "Bottom Camera" << endl;
    }
    else {
        out->camera_param->mode = 0;
        cout << "Front Camera" << endl;
    }
}
