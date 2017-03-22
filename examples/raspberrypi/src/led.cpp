#include "ros/ros.h"
#include "led.h"
#include <iostream>
#include <GPIOClass.h>

using namespace std;

//sudo -i 
//echo "4" > /sys/class/gpio/export
//echo "out" > /sys/class/gpio/gpio4/direction
//echo "1" > /sys/class/gpio/gpio4/value

GPIOClass* gpio4;
Led::Led()
{
    	gpio4 = new GPIOClass("4"); //create new GPIO object to be attached to  GPIO4

    	gpio4->export_gpio(); //export GPIO4
    	gpio4->setdir_gpio("out"); // GPIO4 set to output

    	cout << "Set GPIO pin directions" << endl;
}

void Led::step(const radl_in_t * in, const radl_in_flags_t* iflags,
               radl_out_t * out, radl_out_flags_t* oflags) 
{
	if ( in->button_status->on ) {
		gpio4->setval_gpio("1"); // turn LED ON
	} 
	else 
		gpio4->setval_gpio("0"); // turn LED OFF

	if ( *RADL_THIS->print_data ) {
        	cout << ((in->button_status->on == true) ? "button_status on" : "button_status off") << endl;
	}
}
