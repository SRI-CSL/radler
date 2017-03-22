
#include <iostream>

#include RADL_HEADER


class N2 {
public:

  void step(const radl_in_t* i, const radl_in_flags_t* f,
        radl_out_t* o, radl_out_flags_t* of) {
    std::cout << i->i2->x1 << " (" << STRINGIZE(RADL_NODE_NAME) << ") " << radl_is_stale(f->i2) <<" "<< radl_is_timeout(f->i2) << std::endl;
  }
};

