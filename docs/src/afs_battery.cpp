#include "afs_battery.h"

#include <iostream>

using namespace std;

void AFS_Battery::step(const radl_in_t * i, const radl_in_flags_t* i_f, radl_out_t * o, radl_out_flags_t* o_f) 
{
	double battery = i->battery_status->percentage;

	if (radl_is_stale(i_f->battery_status))
		cout << "battery_status is stale" << endl;
	if (radl_is_timeout(i_f->battery_status))
		cout << "battery_status is timeout" << endl;
	
	if (!radl_is_stale(i_f->battery_status) && !radl_is_timeout(i_f->battery_status)) {
		cout << "afs battery : " << battery << endl;
		if (battery < *RADL_THIS->min_battery) {
			o->mode_change_rtl->val = true;
			//cout << "Return to Takeoff Location" << endl;
		}
		else { 
			o->mode_change_rtl->val = false;
		}
	}
}
