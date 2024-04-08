#include "Consumer.h"
#include <iostream>
#include <string>
#include <cstring>

char plain[6][64] = { 
  "3243f6a8885a308d313198a2e0370734",
  "9dc2c84a37850c11699818605f47958c",
  "59b5088e6dadc3ad5f27a460872d5929",
  "59b5088e6dadc3ad5f27a460872d5929",
  "a02600ecb8ea77625bba6641ed5f5920",
  "5241ead9a89ca31a7147f53a5bf6d96a"
};
char key[6][64] = { 
  "2b7e151628aed2a6abf7158809cf4f3c",
  "2e586692e647f5028ec6fa47a55a2aab",
  "a02600ecb8ea77625bba6641ed5f5920",
  "8d2e60365f17c7df1040d7501b4a7b5a",
  "2d0860dae7fdb0bd4bfab111f615227a",
  "7f498a034f6113a73abd442bade3fb10" 
};

Consumer::Consumer() {
  this->counter = 0;
}

void Consumer::step(const radl_in_t * in, const radl_in_flags_t* inflags,
                      radl_out_t * out, radl_out_flags_t* outflags){
  out->aes->seq = this->counter++;
  std::cout << "seq " << out->aes->seq << std::endl;

  std::copy(std::begin(plain[out->aes->seq % 6]), std::end(plain[out->aes->seq % 6]), std::begin(out->aes->plain));
  std::copy(std::begin(key[out->aes->seq % 6]), std::end(key[out->aes->seq % 6]), std::begin(out->aes->key));
}
