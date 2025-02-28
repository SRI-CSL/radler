#include "hr_sensor.h"

#include <iostream>
#include <random>

using namespace std;

void HR_Sensor::step(const radl_in_t * i, const radl_in_flags_t* i_f, radl_out_t * o, radl_out_flags_t* o_f) 
{
  static random_device rd;
  static mt19937 gen(rd());

  uniform_real_distribution<double> dist(60.0, 100.0);  
  o->hr->hr = dist(gen);
  cout << "HR sensor : " <<  o->hr->hr << endl;
}
