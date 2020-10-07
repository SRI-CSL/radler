#include "afs_altitude.h"

#include <iostream>

using namespace std;

void AFS_Altitude::step(const radl_in_t * i, const radl_in_flags_t* i_f, radl_out_t * o, radl_out_flags_t* o_f) 
{
	double alt = i->altitude->data;

	if (radl_is_stale(i_f->altitude))
		cout << "altitude is stale" << endl;
	if (radl_is_timeout(i_f->altitude))
		cout << "altitude is timeout" << endl;
	
	if (!radl_is_stale(i_f->altitude) && !radl_is_timeout(i_f->altitude)) {
		cout << "current altitude : " << alt << endl;
		if (alt > *RADL_THIS->max_alt || alt < *RADL_THIS->min_alt) {
			o->target_altitude->hold = true;
			if (alt > *RADL_THIS->max_alt)
				o->target_altitude->data = *RADL_THIS->max_alt;
			else
				o->target_altitude->data = *RADL_THIS->min_alt;
			cout << "target altitude : " << o->target_altitude->data << endl;
		}
		else { 
			o->target_altitude->hold = false;
		}
	}
}
