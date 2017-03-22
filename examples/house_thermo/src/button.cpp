#include "button.h"

void Button::step(const radl_in_t * in, const radl_in_flags_t* inflags,
                  radl_out_t * out, radl_out_flags_t* outflags) {
  out->but->status = true;
  out->set->temp = 90;
}


