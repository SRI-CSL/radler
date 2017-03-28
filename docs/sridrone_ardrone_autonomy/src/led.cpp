#include "ros/ros.h"
#include "led.h"
#include <ardrone_autonomy/LedAnim.h>

#include <iostream>

/*
# 0 : BLINK_GREEN_RED
# 1 : BLINK_GREEN
# 2 : BLINK_RED
# 3 : BLINK_ORANGE
# 4 : SNAKE_GREEN_RED
# 5 : FIRE
# 6 : STANDARD
# 7 : RED
# 8 : GREEN
# 9 : RED_SNAKE
# 10: BLANK
# 11: LEFT_GREEN_RIGHT_RED
# 12: LEFT_RED_RIGHT_GREEN
# 13: BLINK_STANDARD
i*/ 

void Led::step(const radl_in_t * in, const radl_in_flags_t* inflags,
                  radl_out_t * out, radl_out_flags_t* outflags) 
{
	double roll = in->navdata->roll; 

        if (roll > 30.0) {
                out->led_anim->id = 11; //LEFT_GREEN_RIGHT_RED;
                std::cout << "[Warning - Roll " << roll << " (>30.0)] LEFT_GREEN_RIGHT_RED" << std::endl;
        }
        else if (roll < -30.0) {
                out->led_anim->id = 12; //LEFT_RED_RIGHT_GREEN;
                std::cout << "[Warning - Roll " << roll << " (-30.0)] LEFT_RED_RIGHT_GREEN" << std::endl;
        }
	else 
                out->led_anim->id = 8; //GREEN;

        std::cout << "LED sets ardrone.setAnimation = " << out->led_anim->id << std::endl;

	ros::ServiceClient client = nh.serviceClient<ardrone_autonomy::LedAnim>("ardrone/setledanimation");

	ardrone_autonomy::LedAnim srv;
	srv.request.type = out->led_anim->id;
	srv.request.freq = 4;
	srv.request.duration = 2;
	
	client.call(srv); 
}
