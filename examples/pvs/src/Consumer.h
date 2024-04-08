#include RADL_HEADER

class Consumer {
  private:
    int counter;
  public:
    Consumer();
    void step(const radl_in_t*, const radl_in_flags_t*, radl_out_t*, radl_out_flags_t*);
};
