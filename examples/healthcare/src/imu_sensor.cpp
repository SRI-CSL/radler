#include "imu_sensor.h"

#include <iostream>
#include <random>

using namespace std;

void IMU_Sensor::step(const radl_in_t * i, const radl_in_flags_t* i_f, radl_out_t * o, radl_out_flags_t* o_f) 
{
	static random_device rd;
  static mt19937 gen(rd());

	uniform_int_distribution<int> dist(0, 200);	
	o->imu->x = dist(gen);
	o->imu->y = dist(gen);
	o->imu->z = dist(gen);
	cout << "IMU sensor : (" <<  o->imu->x << ", " << o->imu->y << ", " << o->imu->z << ")" << endl;
}
