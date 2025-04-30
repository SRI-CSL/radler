#include "house.h"
#include <iostream>

House::House() {
  this->leak_rate = 0.1;
  this->interval = 0.02;
  this->temp = 70.0;
}

void House::step(const radl_in_t * in, const radl_in_flags_t* iflags,
                 radl_out_t * out, radl_out_flags_t * oflags) {
  this->temp += this->interval*(in->heater_rate->rate - this->leak_rate);
  out->house_temp->temp = this->temp;
  oflags->house_temp = 0;
  std::cout << "Temperature : " << out->house_temp->temp << " Heater Rate : " << in->heater_rate->rate << std::endl;
}


