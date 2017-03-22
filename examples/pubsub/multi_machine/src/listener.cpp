#include "listener.h"
#include <iostream>

Listener::Listener() {
  this->counter = 0;
}

void Listener::step(const radl_in_t * in, const radl_in_flags_t* inflags,
                      radl_out_t * out, radl_out_flags_t* outflags){
  if ( this->counter++ % 100 == 0 ) {
    std::cout << "Received " << in->chatter->data << std::endl;
  }
}

