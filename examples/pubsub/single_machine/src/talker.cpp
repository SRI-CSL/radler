#include "talker.h"

Talker::Talker() {
  this->counter = 0;
}

void Talker::step(const radl_in_t * in, const radl_in_flags_t* inflags,
                      radl_out_t * out, radl_out_flags_t* outflags){
  this->counter++; 
  out->chatter->data = this->counter++;
}

