
#include RADL_HEADER

class N1 {
  int32_t cpt;
public:
  N1():cpt(0){};
  void step(const radl_in_t* i, const radl_in_flags_t* f,
        radl_out_t* o, radl_out_flags_t* of) {
    o->o1->x1 = cpt;
    cpt++;
  }
};

