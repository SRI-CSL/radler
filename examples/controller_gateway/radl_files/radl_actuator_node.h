
/*
 * RADL actuator stub subsccribing to a float32
 */

#include <iostream>

#include RADL_HEADER

class Floatsub {
public:
  void step(const radl_in_t* i, const radl_in_flags_t* f,
            radl_out_t* o, radl_out_flags_t* of) {
    std::cout << "Actuator received: " << i->i1->data << std::endl;
  }
};

