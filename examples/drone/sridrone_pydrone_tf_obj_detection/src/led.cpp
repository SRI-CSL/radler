#include "ros/ros.h"
#include "led.h"
#include <iostream>

using namespace std;

extern "C"{
#include <ardrone_api.h>
}

void Led::step(const radl_in_t * in, const radl_in_flags_t* iflags,
               radl_out_t * out, radl_out_flags_t* oflags) 
{
	if ( *RADL_THIS->print_data ) {
		cout << "-----------------------------------" << endl;
	}

    radl_turn_off( radl_TIMEOUT, &oflags->led_anim );
    radl_turn_off( radl_STALE, &oflags->led_anim );

	if ( *RADL_THIS->check_iflags && *RADL_THIS->print_data ) {
		if ( radl_is_stale(iflags->object_detection) ) 
			cout << "object_detection is stale" << endl;
		if ( radl_is_timeout(iflags->object_detection) ) 
			cout << "objec_detection is timeout" << endl;
	}

	int object_id = in->object_detection->id; 

	switch (object_id) {
		case 1: 
			cout << "person" << endl;
			out->led_anim->id = BLINK_GREEN; 
			break;
		case 17: 
			cout << "cat" << endl;
			out->led_anim->id = LEFT_RED_RIGHT_GREEN; 
			break;
		case 18: 
			cout << "dog" << endl;
			out->led_anim->id = LEFT_GREEN_RIGHT_RED; 
			break;
		case 88:
			cout << "teddy bear" << endl;
			out->led_anim->id = BLINK_RED;  
			break;
		default:
			out->led_anim->id = GREEN; 
			break;
	}
		
	if ( *RADL_THIS->print_data ) 
    	cout << "LED sets ardrone.setAnimation = " << out->led_anim->id << endl;
}
