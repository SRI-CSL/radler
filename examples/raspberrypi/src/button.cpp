#include "ros/ros.h"
#include "button.h"
#include <iostream>
#include <GPIOClass.h>

using namespace std;

GPIOClass* gpio17; 
Button::Button()
{
	gpio17 = new GPIOClass("17"); //create new GPIO object to be attached to  GPIO17

    	gpio17->export_gpio(); //export GPIO17
    	gpio17->setdir_gpio("in"); //GPIO17 set to input

    	cout << "Set GPIO pin directions" << endl;
}

void Button::step(const radl_in_t * in, const radl_in_flags_t* iflags,
               radl_out_t * out, radl_out_flags_t* oflags) 
{
        string inputstate;
	gpio17->getval_gpio(inputstate); 

	if(inputstate == "0")
		out->button_status->on = true; 
	else
		out->button_status->on = false; 

	if ( *RADL_THIS->print_data ) {
        	cout << ((out->button_status->on == true) ? "button_status on" : "button_status off") << endl;
	}
}
