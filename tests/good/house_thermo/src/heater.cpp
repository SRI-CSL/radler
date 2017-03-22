#include "heater.h"

void Heater::step(const radl_in_t * in, const radl_in_flags_t* inflags,
                  radl_out_t * out, radl_out_flags_t* outflags) {
  if (in->heater_switch->switch_on) {
    out->heater_rate->rate = 3.0;
  } else {
    out->heater_rate->rate = 0.0;
  }
}


