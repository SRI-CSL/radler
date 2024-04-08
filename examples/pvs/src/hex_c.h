//Code generated using pvs2ir
#ifndef _hex_h 
#define _hex_h

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

#include "integertypes_c.h"

#include "exp2_c.h"

#include "euclidean_division_c.h"

#include "ordinals_c.h"

#include "ordstruct_adt_c.h"

#include "finite_sequences_c.h"

#include "real_defs_c.h"

#include "simplifications_c.h"

//cc -O3 -Wall -o hex -I /Users/e21660/shankar/pvs.git//include /Users/e21660/shankar/pvs.git//lib/pvslib.c  -I /Users/e21660/shankar/pvs.git/lib /Users/e21660/shankar/pvs.git/lib/bytestrings_c.c /Users/e21660/shankar/pvs.git/lib/gen_strings_c.c /Users/e21660/shankar/pvs.git/lib/strings_c.c /Users/e21660/shankar/pvs.git/lib/integertypes_c.c /Users/e21660/shankar/pvs.git/lib/exp2_c.c /Users/e21660/shankar/pvs.git/lib/euclidean_division_c.c /Users/e21660/shankar/pvs.git/lib/ordinals_c.c /Users/e21660/shankar/pvs.git/lib/ordstruct_adt_c.c /Users/e21660/shankar/pvs.git/lib/finite_sequences_c.c /Users/e21660/shankar/pvs.git/lib/real_defs_c.c hex_c.c simplifications_c.c -lgmp 

struct hex_array_0_s { uint32_t count;
        uint32_t size;
         uint32_t max;
         uint8_t elems[]; };
typedef struct hex_array_0_s * hex_array_0_t;

extern hex_array_0_t new_hex_array_0(uint32_t size);

extern void release_hex_array_0(hex_array_0_t x);

extern hex_array_0_t copy_hex_array_0(hex_array_0_t x);

extern bool_t equal_hex_array_0(hex_array_0_t x, hex_array_0_t y);
typedef struct actual_hex_array_0_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr;} * actual_hex_array_0_t;

void release_hex_array_0_ptr(pointer_t x, type_actual_t hex_array_0);
extern bool_t equal_hex_array_0_ptr(pointer_t x, pointer_t y, type_actual_t T);

actual_hex_array_0_t actual_hex_array_0(void);

extern hex_array_0_t update_hex_array_0(hex_array_0_t x, uint32_t i, uint8_t v);

extern hex_array_0_t upgrade_hex_array_0(hex_array_0_t x, uint32_t i, uint8_t v);



struct hex_array_1_s { uint32_t count;
        uint32_t size;
         uint32_t max;
         uint32_t elems[]; };
typedef struct hex_array_1_s * hex_array_1_t;

extern hex_array_1_t new_hex_array_1(uint32_t size);

extern void release_hex_array_1(hex_array_1_t x);

extern hex_array_1_t copy_hex_array_1(hex_array_1_t x);

extern bool_t equal_hex_array_1(hex_array_1_t x, hex_array_1_t y);
typedef struct actual_hex_array_1_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr;} * actual_hex_array_1_t;

void release_hex_array_1_ptr(pointer_t x, type_actual_t hex_array_1);
extern bool_t equal_hex_array_1_ptr(pointer_t x, pointer_t y, type_actual_t T);

actual_hex_array_1_t actual_hex_array_1(void);

extern hex_array_1_t update_hex_array_1(hex_array_1_t x, uint32_t i, uint32_t v);

extern hex_array_1_t upgrade_hex_array_1(hex_array_1_t x, uint32_t i, uint32_t v);



extern bool_t hex__digitp(uint8_t ivar_1);

extern bool_t hex__hexalphap(uint8_t ivar_1);

extern bool_t hex__hexdigitp(uint8_t ivar_1);

extern uint8_t hex__hexvalue(uint8_t ivar_2);

extern uint8_t hex__hex2byte(uint8_t ivar_2, uint8_t ivar_3);

extern bytestrings__bytestring_t hex__hex2bytestring(bytestrings__bytestring_t ivar_1);

extern bytestrings__bytestring_t hex__test_hex2bytestring(void);

extern uint8_t hex__hex0(uint8_t ivar_2);

extern uint8_t hex__hex1(uint8_t ivar_2);

extern bytestrings__bytestring_t hex__bytestring2hexstring(bytestrings__bytestring_t ivar_2);

extern bytestrings__bytestring_t hex__test_bytestring2hexstring(void);

extern uint32_t hex__bytes2uint32(bytestrings__bytestring_t ivar_3, uint32_t ivar_4);

extern uint16_t hex__bytes2uint16(bytestrings__bytestring_t ivar_3, uint32_t ivar_4);

extern uint8_t hex__bytes2uint8(bytestrings__bytestring_t ivar_3, uint32_t ivar_4);

extern uint64_t hex__bytes2uint64(bytestrings__bytestring_t ivar_3, uint32_t ivar_4);

extern bool_t hex__equalUpto(bytestrings__bytestring_t ivar_1, bytestrings__bytestring_t ivar_2, uint32_t ivar_3);

extern hex_array_1_t hex__bytes2uint32array(bytestrings__bytestring_t ivar_9);
#endif