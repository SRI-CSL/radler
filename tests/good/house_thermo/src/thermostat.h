#include "radl__thermostat.h"

class Thermostat {
 private:
  float set_temp;
  bool status;
  float tol;
 public:
  Thermostat();
  void step(const radl_in_t*, const radl_in_flags_t*, radl_out_t*, radl_out_flags_t*);
};
