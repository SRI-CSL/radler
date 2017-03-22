
/*
 * RADL device stub publishing an increasing int32
 */

#include <iostream>

#include RADL_HEADER

class Intpub {
  int32_t cpt;
public:
  void step(const radl_in_t* i, const radl_in_flags_t* f,
            radl_out_t* o, radl_out_flags_t* of) {
    o->o1->data = cpt;
    std::cout << "Device publishing: " << cpt << std::endl;
    cpt++;
  }
};

