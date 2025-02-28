#include "hr_display.h"

#include <iostream>

using namespace std;

void HR_Display::step(const radl_in_t * i, const radl_in_flags_t* i_f, radl_out_t * o, radl_out_flags_t* o_f) 
{
	bool beep = i->hr_warning->val;

	if (radl_is_stale(i_f->hr_warning))
		cout << "hr_warning is stale" << endl;
	if (radl_is_timeout(i_f->hr_warning))
		cout << "hr_warning is timeout" << endl;
	
	if (!radl_is_stale(i_f->hr_warning) && !radl_is_timeout(i_f->hr_warning)) {
    if (beep)
	    cout << "HR display : WARNING" << endl;
	}
}
