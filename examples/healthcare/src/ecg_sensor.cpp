#include "ecg_sensor.h"

#include <iostream>
#include <random>

using namespace std;

void ECG_Sensor::step(const radl_in_t * i, const radl_in_flags_t* i_f, radl_out_t * o, radl_out_flags_t* o_f) 
{
  static random_device rd;
  static mt19937 gen(rd());

  uniform_int_distribution<int> dist(100, 200); 
  cout << "ECG Sensor :";  
  for (int i=0; i<60; i++) {
    o->ecg->ecg[i] = dist(gen);
    cout << " " <<  o->ecg->ecg[i];
  }
  cout << endl;  
}
