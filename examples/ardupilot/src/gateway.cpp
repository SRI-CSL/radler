#include "gateway.h"

#include <iostream>

using namespace std;

Gateway::Gateway() 
{
	mode_srv = nh.serviceClient<mavros_msgs::SetMode>("/mavros/set_mode");
	bat_sub = nh.subscribe("/mavros/battery", 2, &Gateway::battery_state_cb, this);
	alt_sub = nh.subscribe("/mavros/global_position/rel_alt", 2, &Gateway::altitude_cb, this);
	alt_pub = nh.advertise<geometry_msgs::PoseStamped>("/mavros/setpoint_position/local", 2);
}

void Gateway::step(const radl_in_t* i, const radl_in_flags_t* i_f, radl_out_t* o, radl_out_flags_t* o_f) 
{
	mavros_msgs::SetMode srv_setMode;
	srv_setMode.request.base_mode = 0;

	if (this->bat_out_mbox) {
		o->battery_status->percentage = this->bat_out_mbox->percentage;
		cout << "gateway battery : " << o->battery_status->percentage  << endl;
		radl_turn_off(radl_STALE, &o_f->battery_status);
	} else {
		radl_turn_on(radl_STALE, &o_f->battery_status);
	}
	radl_turn_off(radl_TIMEOUT, &o_f->battery_status);

	if (radl_is_stale(i_f->mode_change_rtl))
		cout << "mode_change_rtl is stale" << endl;
	if (radl_is_timeout(i_f->mode_change_rtl))
		cout << "mode_change_rtl is timeout" << endl;
	
	if (!radl_is_stale(i_f->mode_change_rtl) && !radl_is_timeout(i_f->mode_change_rtl)) {
		if (i->mode_change_rtl->val) { 
			srv_setMode.request.custom_mode = "RTL";
			cout << "mode change to RTL" << endl;
		}
		mode_srv.call(srv_setMode);
	}

	if (this->alt_out_mbox) {
		o->altitude->data = this->alt_out_mbox->data;
		cout << "gateway altitude : " << o->altitude->data << endl;
		radl_turn_off(radl_STALE, &o_f->altitude);
	} else {
		radl_turn_on(radl_STALE, &o_f->altitude);
	}
	radl_turn_off(radl_TIMEOUT, &o_f->altitude);

	if (radl_is_stale(i_f->mode_change_althold))
		cout << "mode_change_althold is stale" << endl;
	if (radl_is_timeout(i_f->mode_change_althold))
		cout << "mode_change_althold is timeout" << endl;
	
	if (!radl_is_stale(i_f->mode_change_althold) && !radl_is_timeout(i_f->mode_change_althold)) {
		if (i->target_altitude->hold) {
			geometry_msgs::PoseStamped msg;
			msg.pose.position.z = i->target_altitude->data;
			cout << "gateway target altitude : " << i->target_altitude->data << endl;
			alt_pub.publish(msg);
		}
	}
/*
	if (!radl_is_stale(i_f->mode_change_althold) && !radl_is_timeout(i_f->mode_change_althold)) {
		if (i->mode_change_althold->val) {
			srv_setMode.request.custom_mode = "ALT_HOLD";
			cout << "mode change to ALT_HOLD" << endl;
		}
		mode_srv.call(srv_setMode);
	}
*/
}

void Gateway::battery_state_cb(const sensor_msgs::BatteryState::ConstPtr& bs) 
{
	this->bat_out_mbox = bs;
}

void Gateway::altitude_cb(const std_msgs::Float64::ConstPtr& alt) 
{
	this->alt_out_mbox = alt;
}
