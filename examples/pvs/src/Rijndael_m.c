#include "Rijndael_c.h"

static bytestrings__bytestring_t
make_bytestring(const char *arg)
{   size_t len = strlen(arg);
    uint32_t *array = malloc(len * sizeof(uint32_t));
    
    for (uint32_t i = 0; i < len; ++i) {
        array[i] = arg[i] & 0xff;
    }
    stringliteral_t sl = mk_string(len, array);
    strings__string_t st = strings__make_string(len, (strings_array_2_t)sl);
    bytestrings__bytestring_t bs = bytestrings__mk_bytestring(st);
    free(array); //sl and st are freed in strings__make_string and bytestrings_mk_bytestring
    return bs;
}

static void
print_bytestring(const char *what, bytestrings__bytestring_t bs)
{
    uint32_t i;
    printf("\n%s: ", what);
    for (i = 0; i < bs->length; ++i) {
        printf("%02x", bs->seq->elems[i]);
    }
    printf("\n");
}
uint32_t print_hexstring(bytestrings__bytestring_t s){
  /* printf("\nhextest0: %#X", 0); */
  /* printf("\nhextest0: %#X", 10); */
  /* printf("\nhextest0: %#X", 20); */
  /* printf("\nhextest0: %#X", 40); */
  /* printf("\nhextest0: %#X", 80); */
  /* printf("\nhextest0: %#X", 160); */
  /* printf("\nhextest0: %#X", 240);   */
  //  printf("\n");
  /* printf("\ns->length = %"PRIu32"\n", s->length);   */
  /* for (uint32_t i = 0; i < s->length; i++){ */
  /*   printf("%"PRIu8"", s->seq->elems[i]); */
  /* }; */
  printf("\n");
  for (uint32_t i = 0; i < s->length; i++){
    printf("%c", s->seq->elems[i]);
  };

  return 1;
};

int main(){
  double start = get_cpu_time();
  //  printf("\n HMAC__test1()");
  
  //  print_hexstring((bytestrings__bytestring_t)Rijndael__testRijndael1());
  //bytestrings__bytestring_t st1 = Rijndael__testRijndael1();
  //  printf("\n HMAC__test2()");
  //  printf("\n HMAC__test2()");
  //  printf("\n HMAC__test2()");    
  //  print_hexstring((bytestrings__bytestring_t)Rijndael__testInvRijndael1());
  //test 1
  printf("\nRijndael test 1");
  bytestrings__bytestring_t plain1 = make_bytestring("3243f6a8885a308d313198a2e0370734");
  bytestrings__bytestring_t key1 = make_bytestring("2b7e151628aed2a6abf7158809cf4f3c");
  print_hexstring((bytestrings__bytestring_t)Rijndael__testRijndael(plain1, key1));
  printf("\nExpected Ciphertext: 39 25 84 1d 02 dc 09 fb dc 11 85 97 19 6a 0b 32");
  //test 2
  printf("\nRijndael test 2");
  bytestrings__bytestring_t plain2 = make_bytestring("9dc2c84a37850c11699818605f47958c");
  bytestrings__bytestring_t key2 = make_bytestring("2e586692e647f5028ec6fa47a55a2aab");
  print_hexstring((bytestrings__bytestring_t)Rijndael__testRijndael(plain2, key2));
  printf("\nExpected Ciphertext: 06 99 02 32 58 82 9e 6b 99 02 56 16 53 fd 3b e2");
  //test 3
  printf("\nRijndael test 3");
  bytestrings__bytestring_t plain3 = make_bytestring("59b5088e6dadc3ad5f27a460872d5929");
  bytestrings__bytestring_t key3 = make_bytestring("a02600ecb8ea77625bba6641ed5f5920");
  print_hexstring((bytestrings__bytestring_t)Rijndael__testRijndael(plain3, key3));
  printf("\nExpected Ciphertext:  8b b4 34 73 4a a5 c5 c9 1b 90 8e 3e 82 e2 69 c0");
  //test 4
  printf("\nRijndael test 4");
  bytestrings__bytestring_t plain4 = make_bytestring("59b5088e6dadc3ad5f27a460872d5929");
  bytestrings__bytestring_t key4 = make_bytestring("8d2e60365f17c7df1040d7501b4a7b5a");
  print_hexstring((bytestrings__bytestring_t)Rijndael__testRijndael(plain4, key4));
  printf("\nExpected Ciphertext: e6 42 55 6d 1c 30 1b af 2e ba 96 31 49 cd ec 79");
  //test 5
  printf("\nRijndael test 5");
  bytestrings__bytestring_t plain5 = make_bytestring("a02600ecb8ea77625bba6641ed5f5920");
  bytestrings__bytestring_t key5 = make_bytestring("2d0860dae7fdb0bd4bfab111f615227a");
  print_hexstring((bytestrings__bytestring_t)Rijndael__testRijndael(plain5, key5));
  printf("\nExpected Ciphertext: 7c 8a 9b 39 a4 f5 08 bf 99 3e 2e 91 9c a6 98 55");
  //test 6
  printf("\nRijndael test 6");
  bytestrings__bytestring_t plain6 = make_bytestring("5241ead9a89ca31a7147f53a5bf6d96a");
  bytestrings__bytestring_t key6 = make_bytestring("7f498a034f6113a73abd442bade3fb10");
  print_hexstring((bytestrings__bytestring_t)Rijndael__testRijndael(plain6, key6));
  printf("\nExpected Ciphertext: e1 e5 78 94 f6 b8 dd 99 f9 c0 7e c8 c1 ae 0a 6d");
  
  //bytestrings__bytestring_t st2 = Rijndael__testInvRijndael1();
  //  printf("\n HMAC__test3()");
  //  printf("\n HMAC__test3()");
  //  printf("\n HMAC__test3()");      
  double end = get_cpu_time();
  printf("\n CPU Time = %f seconds\n", end - start);
  return 0;
}
