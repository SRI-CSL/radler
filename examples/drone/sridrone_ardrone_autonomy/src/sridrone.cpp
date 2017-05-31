#include "ros/ros.h"
#include "sridrone.h"
#include <ardrone_autonomy/Navdata.h>

#include <iostream>

#include <image_transport/image_transport.h>
#include <sensor_msgs/image_encodings.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

static const std::string SRC_WINDOW = "ardrone";
static const std::string DST_WINDOW = "houghline";

ardrone_autonomy::Navdata lastNavdataReceived; 

void navdataCb(const ardrone_autonomy::NavdataConstPtr navdataPtr) {
	lastNavdataReceived = *navdataPtr;
}

void process(const sensor_msgs::ImageConstPtr& mgs)
{
    cv_bridge::CvImageConstPtr cv_ptr;
    try
    {
        cv_ptr = cv_bridge::toCvCopy(mgs, sensor_msgs::image_encodings::RGB8);
    }
    catch (cv_bridge::Exception& e)
    {
        return;
    }
    
    Mat dst, cdst;
    Canny(cv_ptr->image, dst, 50, 200, 3);
    cvtColor(dst, cdst, COLOR_GRAY2BGR);

    vector<Vec4i> lines;
    HoughLinesP(dst, lines, 1, CV_PI/180, 50, 50, 10 );
    for( size_t i = 0; i < lines.size(); i++ )
    {
        Vec4i l = lines[i];
        line(cdst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, LINE_AA);
    }

    waitKey(1);
    imshow(SRC_WINDOW, cv_ptr->image);
    waitKey(1);
    imshow(DST_WINDOW, cdst);
    waitKey(1);
}

SRIDrone::SRIDrone()
{
	navdata_sub = nh.subscribe<ardrone_autonomy::Navdata>("/ardrone/navdata", 10, navdataCb); 
    if(!navdata_sub)
        cout << "ERROR:: subscribe to /ardrone/navdata failed" << endl;

	if (*RADL_THIS->opencv_houghline) {
        image_transport::ImageTransport it(nh);
        image_sub = it.subscribe("/ardrone/image_raw", 1, process);
        if(!image_sub)
            cout << "ERROR:: subscribe to /ardrone/image_raw failed" << endl;

        waitKey(1);
        namedWindow(SRC_WINDOW);
        waitKey(1);
        namedWindow(DST_WINDOW);
        waitKey(1);
    }
}

void SRIDrone::step(const radl_in_t * in, const radl_in_flags_t* iflags,
                 radl_out_t * out, radl_out_flags_t * oflags) 
{
    cout << "-----------------------------------" << endl;

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

    cout << "ardrone.roll  = " << roll  << " [deg]" << endl;
    cout << "ardrone.pitch = " << pitch << " [deg]" << endl;
    cout << "ardrone.yaw   = " << yaw   << " [deg]" << endl;
    cout << "ardrone.altitude = " << altitude << " [m]" << endl;
    cout << "ardrone.vx = " << v_x << " [m/s]" << endl;
    cout << "ardrone.vy = " << v_y << " [m/s]" << endl;
    cout << "ardrone.vz = " << v_z << " [m/s]" << endl;
    cout << "ardrone.battery = " << battery << " [%]" << endl;
}
