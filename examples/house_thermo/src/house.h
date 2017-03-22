#include "radl__house.h"

class House {
 private:
  float temp;
  float leak_rate;
  float interval;
 public:
  House();
  void step(const radl_in_t*, const radl_in_flags_t*, radl_out_t*, radl_out_flags_t*);
};



