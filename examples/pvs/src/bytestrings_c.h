//Code generated using pvs2ir
#ifndef _bytestrings_h 
#define _bytestrings_h

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

#include "gen_strings_c.h"

#include "strings_c.h"

#include "integertypes_c.h"

#include "exp2_c.h"

#include "euclidean_division_c.h"

#include "real_defs_c.h"

#include "ordinals_c.h"

#include "ordstruct_adt_c.h"

//cc -O3 -Wall -o bytestrings -I /Users/e21660/shankar/pvs.git//include /Users/e21660/shankar/pvs.git//lib/pvslib.c  -I /Users/e21660/shankar/pvs.git/lib /Users/e21660/shankar/pvs.git/lib/gen_strings_c.c /Users/e21660/shankar/pvs.git/lib/strings_c.c /Users/e21660/shankar/pvs.git/lib/integertypes_c.c /Users/e21660/shankar/pvs.git/lib/exp2_c.c /Users/e21660/shankar/pvs.git/lib/euclidean_division_c.c /Users/e21660/shankar/pvs.git/lib/real_defs_c.c /Users/e21660/shankar/pvs.git/lib/ordinals_c.c /Users/e21660/shankar/pvs.git/lib/ordstruct_adt_c.c bytestrings_c.c -lgmp 

struct bytestrings_array_0_s { uint32_t count;
        uint32_t size;
         uint32_t max;
         uint8_t elems[]; };
typedef struct bytestrings_array_0_s * bytestrings_array_0_t;

extern bytestrings_array_0_t new_bytestrings_array_0(uint32_t size);

extern void release_bytestrings_array_0(bytestrings_array_0_t x);

extern bytestrings_array_0_t copy_bytestrings_array_0(bytestrings_array_0_t x);

extern bool_t equal_bytestrings_array_0(bytestrings_array_0_t x, bytestrings_array_0_t y);
typedef struct actual_bytestrings_array_0_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr;} * actual_bytestrings_array_0_t;

void release_bytestrings_array_0_ptr(pointer_t x, type_actual_t bytestrings_array_0);
extern bool_t equal_bytestrings_array_0_ptr(pointer_t x, pointer_t y, type_actual_t T);

actual_bytestrings_array_0_t actual_bytestrings_array_0(void);

extern bytestrings_array_0_t update_bytestrings_array_0(bytestrings_array_0_t x, uint32_t i, uint8_t v);

extern bytestrings_array_0_t upgrade_bytestrings_array_0(bytestrings_array_0_t x, uint32_t i, uint8_t v);



struct bytestrings__bytestring_s {
        uint32_t count; 
        uint32_t length;
        bytestrings_array_0_t seq;};
typedef struct bytestrings__bytestring_s * bytestrings__bytestring_t;

extern bytestrings__bytestring_t new_bytestrings__bytestring(void);

extern void release_bytestrings__bytestring(bytestrings__bytestring_t x);

extern bytestrings__bytestring_t copy_bytestrings__bytestring(bytestrings__bytestring_t x);

extern bool_t equal_bytestrings__bytestring(bytestrings__bytestring_t x, bytestrings__bytestring_t y);
typedef struct actual_bytestrings__bytestring_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr;} * actual_bytestrings__bytestring_t;

void release_bytestrings__bytestring_ptr(pointer_t x, type_actual_t bytestrings__bytestring);
extern bool_t equal_bytestrings__bytestring_ptr(pointer_t x, pointer_t y, actual_bytestrings__bytestring_t T);

actual_bytestrings__bytestring_t actual_bytestrings__bytestring(void);

extern bytestrings__bytestring_t update_bytestrings__bytestring_length(bytestrings__bytestring_t x, uint32_t v);

extern bytestrings__bytestring_t update_bytestrings__bytestring_seq(bytestrings__bytestring_t x, bytestrings_array_0_t v);



extern uint32_t bytestrings__bytestring_bound(void);

extern uint32_t bytestrings__length(bytestrings__bytestring_t ivar_2);

extern uint8_t bytestrings__get(bytestrings__bytestring_t ivar_3, uint32_t ivar_4);

extern bytestrings__bytestring_t bytestrings__null(void);

extern bytestrings__bytestring_t bytestrings__unit(uint8_t ivar_1);

extern bytestrings__bytestring_t bytestrings__mk_bytestring(strings__string_t ivar_1);

extern bytestrings__bytestring_t bytestrings__doubleplus(bytestrings__bytestring_t ivar_1, bytestrings__bytestring_t ivar_2);

extern uint32_t bytestrings__strdiff_rec(bytestrings__bytestring_t ivar_12, bytestrings__bytestring_t ivar_13, uint32_t ivar_14);

extern uint32_t bytestrings__strdiff(bytestrings__bytestring_t ivar_6, bytestrings__bytestring_t ivar_7);

extern int8_t bytestrings__strcmp(bytestrings__bytestring_t ivar_2, bytestrings__bytestring_t ivar_3);

extern bytestrings__bytestring_t bytestrings__prefix(bytestrings__bytestring_t ivar_1, uint32_t ivar_2);

extern bytestrings__bytestring_t bytestrings__suffix(bytestrings__bytestring_t ivar_1, uint32_t ivar_2);

extern bytestrings__bytestring_t bytestrings__substr(bytestrings__bytestring_t ivar_4, uint32_t ivar_5, mpz_ptr_t ivar_7);

extern bool_t bytestrings__ascii_bytestringp(bytestrings__bytestring_t ivar_1);
#endif