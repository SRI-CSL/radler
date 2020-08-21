#include "gateway.h"

#include <iostream>

using namespace std;

Gateway::Gateway() 
{
	sub = nh.subscribe("/mavros/battery", 2, &Gateway::battery_state_cb, this);
	client = nh.serviceClient<mavros_msgs::SetMode>("/mavros/set_mode");
}

void Gateway::step(const radl_in_t* i, const radl_in_flags_t* i_f, radl_out_t* o, radl_out_flags_t* o_f) 
{
	if (this->out_mbox) {
		o->battery_status->percentage = this->out_mbox->percentage;
		cout << "gateway battery : " << o->battery_status->percentage  << endl;
		radl_turn_off(radl_STALE, &o_f->battery_status);
	} else {
		radl_turn_on(radl_STALE, &o_f->battery_status);
	}

	if (radl_is_stale(i_f->mode_change))
		cout << "mode change is stale" << endl;
	if (radl_is_timeout(i_f->mode_change))
		cout << "mode change is timeout" << endl;
	
	if (!radl_is_stale(i_f->mode_change) && !radl_is_timeout(i_f->mode_change)) {
		if (i->mode_change->land) { 
			mavros_msgs::SetMode srv_setMode;
			srv_setMode.request.base_mode = 0;
			srv_setMode.request.custom_mode = "LAND";
			client.call(srv_setMode);
			cout << "mode change to LAND" << endl;
		}
	}
}

void Gateway::battery_state_cb(const sensor_msgs::BatteryState::ConstPtr& bs) 
{
	this->out_mbox = bs;
}
