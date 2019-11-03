#include "listener.h"
#include <iostream>

Listener::Listener() {
}

void Listener::step(const radl_in_t * in, const radl_in_flags_t* inflags,
                      radl_out_t * out, radl_out_flags_t* outflags){
  if ( !radl_is_stale(inflags->chatter) && !radl_is_timeout (inflags->chatter) )
    std::cout << "Received " << in->chatter->data << std::endl;
}
