#include "Rijndael.h"
#include <iostream>
#include <string>
#include <algorithm>

#include <gmpxx.h>

extern "C" {
#include "bytestrings_c.h" 
#include "pvslib.h"
#include "Rijndael_c.h"
#include "strings_c.h"

static bytestrings__bytestring_t
make_bytestring(const char *arg)
{   size_t len = strlen(arg);
    uint32_t *array = (uint32_t *) malloc(len * sizeof(uint32_t));

    for (uint32_t i = 0; i < len; ++i) {
        array[i] = arg[i] & 0xff;
    }
    stringliteral_t sl = mk_string(len, array);
    strings__string_t st = strings__make_string(len, (strings_array_2_t)sl);
    bytestrings__bytestring_t bs = bytestrings__mk_bytestring(st);
    free(array); //sl and st are freed in strings__make_string and bytestrings_mk_bytestring
    return bs;
}
uint32_t print_hexstring(bytestrings__bytestring_t s){
  printf("\n");
  for (uint32_t i = 0; i < s->length; i++){
    printf("%c", s->seq->elems[i]);
  };

  return 1;
};
}

Rijndael::Rijndael() {
}

void Rijndael::step(const radl_in_t * in, const radl_in_flags_t* inflags,
                      radl_out_t * out, radl_out_flags_t* outflags)
{
  if ( !radl_is_stale(inflags->aes) && !radl_is_timeout (inflags->aes) ) {
    std::cout << std::endl << "seq " << in->aes->seq;

    char tmp[64];
    std::copy(std::begin(in->aes->plain), std::end(in->aes->plain), std::begin(tmp));
    bytestrings__bytestring_t plain1 = make_bytestring(tmp); 
    std::copy(std::begin(in->aes->key), std::end(in->aes->key), std::begin(tmp));
    bytestrings__bytestring_t key1 = make_bytestring(tmp); 

    print_hexstring((bytestrings__bytestring_t)Rijndael__testRijndael(plain1, key1));
  } else {
    std::cout << std::endl << "stale or timeout" << std::endl;
  }
}

