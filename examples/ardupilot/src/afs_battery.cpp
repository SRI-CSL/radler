#include "afs_battery.h"

#include <iostream>

using namespace std;

void AFS_Battery::step(const radl_in_t * i, const radl_in_flags_t* i_f, radl_out_t * o, radl_out_flags_t* o_f) 
{
	double battery = i->battery_status->percentage;

	if (radl_is_stale(i_f->battery_status))
		cout << "battery status is stale" << endl;
	if (radl_is_timeout(i_f->battery_status))
		cout << "battery status is timeout" << endl;
	
	if (!radl_is_stale(i_f->battery_status) && !radl_is_timeout(i_f->battery_status)) {
		if (battery < 0.9)	{
			o->mode_change->land = true;
			cout << "afs battery : " << battery << " Emergency Landing" << endl;
		}
		else { 
			o->mode_change->land = false;
			cout << "afs battery : " << battery << endl;
		}
	}
}
