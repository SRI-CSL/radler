#include RADL_HEADER

class Keyboard {
  public:
    Keyboard();
    void step(const radl_in_t*, const radl_in_flags_t*, radl_out_t*, radl_out_flags_t*);
}; 
