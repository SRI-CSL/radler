#include "rr_sensor.h"

#include <iostream>
#include <random>

using namespace std;

void RR_Sensor::step(const radl_in_t * i, const radl_in_flags_t* i_f, radl_out_t * o, radl_out_flags_t* o_f) 
{
	static random_device rd;
  static mt19937 gen(rd());

	uniform_int_distribution<int> dist(12, 20);	
	o->rr->rr = dist(gen);
	cout << "RR sensor : " <<  o->rr->rr << endl;
}
