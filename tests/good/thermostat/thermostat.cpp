
#include "thermostat.h"

Thermostat::Thermostat() {
  this->set_temp = 75.0;
  this->status = false;
  this->tol = 2.0;
}

void Thermostat::step(const radl_in_t * in, const radl_in_flags_t* inflags,
                      radl_out_t * out, radl_out_flags_t* outflags){
}

