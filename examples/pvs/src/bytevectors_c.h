//Code generated using pvs2ir
#ifndef _bytevectors_h 
#define _bytevectors_h

#include <stdio.h>

#include <stdlib.h>

#include <inttypes.h>

#include <stdbool.h>

#include <stdarg.h>

#include <string.h>

#include <fcntl.h>

#include <math.h>

#include <sys/mman.h>

#include <sys/stat.h>

#include <sys/types.h>

#include <gmp.h>

#include "pvslib.h"

#include "bytestrings_c.h"

#include "gen_strings_c.h"

#include "strings_c.h"

#include "ordinals_c.h"

#include "ordstruct_adt_c.h"

#include "integer_bv_ops_c.h"

#include "bv_c.h"

#include "bit_c.h"

#include "integertypes_c.h"

#include "exp2_c.h"

#include "euclidean_division_c.h"

#include "real_defs_c.h"

//cc -O3 -Wall -o bytevectors -I /Users/e21660/shankar/pvs.git//include /Users/e21660/shankar/pvs.git//lib/pvslib.c  -I /Users/e21660/shankar/pvs.git/lib /Users/e21660/shankar/pvs.git/lib/bytestrings_c.c /Users/e21660/shankar/pvs.git/lib/gen_strings_c.c /Users/e21660/shankar/pvs.git/lib/strings_c.c /Users/e21660/shankar/pvs.git/lib/ordinals_c.c /Users/e21660/shankar/pvs.git/lib/ordstruct_adt_c.c /Users/e21660/shankar/pvs.git/lib/integer_bv_ops_c.c /Users/e21660/shankar/pvs.git/lib/bv_c.c /Users/e21660/shankar/pvs.git/lib/bit_c.c /Users/e21660/shankar/pvs.git/lib/integertypes_c.c /Users/e21660/shankar/pvs.git/lib/exp2_c.c /Users/e21660/shankar/pvs.git/lib/euclidean_division_c.c /Users/e21660/shankar/pvs.git/lib/real_defs_c.c bytevectors_c.c -lgmp 

struct bytevectors__byv_s { uint32_t count;
        uint32_t size;
         uint32_t max;
         uint8_t elems[]; };
typedef struct bytevectors__byv_s * bytevectors__byv_t;

extern bytevectors__byv_t new_bytevectors__byv(uint32_t size);

extern void release_bytevectors__byv(bytevectors__byv_t x, uint32_t bytevectors__n);

extern bytevectors__byv_t copy_bytevectors__byv(bytevectors__byv_t x);

extern bool_t equal_bytevectors__byv(bytevectors__byv_t x, bytevectors__byv_t y, uint32_t bytevectors__n);
typedef struct actual_bytevectors__byv_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; uint32_t bytevectors__n;} * actual_bytevectors__byv_t;

void release_bytevectors__byv_ptr(pointer_t x, type_actual_t bytevectors__byv);
extern bool_t equal_bytevectors__byv_ptr(pointer_t x, pointer_t y, type_actual_t T);

actual_bytevectors__byv_t actual_bytevectors__byv(uint32_t bytevectors__n);

extern bytevectors__byv_t update_bytevectors__byv(bytevectors__byv_t x, uint32_t i, uint8_t v, uint32_t bytevectors__n);

extern bytevectors__byv_t upgrade_bytevectors__byv(bytevectors__byv_t x, uint32_t i, uint8_t v, uint32_t bytevectors__n);



extern bytevectors__byv_t bytevectors__byvand(uint32_t bytevectors__n, bytevectors__byv_t ivar_2, bytevectors__byv_t ivar_3);

extern bytevectors__byv_t bytevectors__byvor(uint32_t bytevectors__n, bytevectors__byv_t ivar_2, bytevectors__byv_t ivar_3);

extern bytevectors__byv_t bytevectors__byvxor(uint32_t bytevectors__n, bytevectors__byv_t ivar_2, bytevectors__byv_t ivar_3);

extern bytevectors__byv_t bytevectors__byvnot(uint32_t bytevectors__n, bytevectors__byv_t ivar_2);

extern bytevectors__byv_t bytevectors__byvleftrot(uint32_t bytevectors__n, bytevectors__byv_t ivar_2, uint32_t ivar_3);

extern uint32_t bytevectors__nextindex(uint32_t bytevectors__n, uint32_t ivar_2);

extern uint32_t bytevectors__precindex(uint32_t bytevectors__n, uint32_t ivar_2);

extern bytevectors__byv_t bytevectors__byvrightrot(uint32_t bytevectors__n, bytevectors__byv_t ivar_2, uint32_t ivar_3);

extern bytevectors__byv_t bytevectors__byvbitleftrot(uint32_t bytevectors__n, bytevectors__byv_t ivar_2, uint8_t ivar_3);

extern bytevectors__byv_t bytevectors__byvbitrightrot(uint32_t bytevectors__n, bytevectors__byv_t ivar_2, uint8_t ivar_3);

extern bytevectors__byv_t bytevectors__byvleftrotate(uint32_t bytevectors__n, bytevectors__byv_t ivar_5, mpz_ptr_t ivar_6);

extern bytevectors__byv_t bytevectors__byvrightrotate(uint32_t bytevectors__n, bytevectors__byv_t ivar_5, mpz_ptr_t ivar_6);

extern bytevectors__byv_t bytevectors__byvXOR(uint32_t bytevectors__n, bytevectors__byv_t ivar_2, bytevectors__byv_t ivar_3);

extern bytestrings__bytestring_t bytevectors__byv2bytestring(uint32_t bytevectors__n, bytevectors__byv_t ivar_1);
#endif