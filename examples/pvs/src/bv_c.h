//Code generated using pvs2ir
#ifndef _bv_h 
#define _bv_h

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

#include "bit_c.h"

#include "integertypes_c.h"

#include "exp2_c.h"

#include "euclidean_division_c.h"

#include "real_defs_c.h"

//cc -O3 -Wall -o bv -I /Users/e21660/shankar/pvs.git//include /Users/e21660/shankar/pvs.git//lib/pvslib.c  -I /Users/e21660/shankar/pvs.git/lib /Users/e21660/shankar/pvs.git/lib/bit_c.c /Users/e21660/shankar/pvs.git/lib/integertypes_c.c /Users/e21660/shankar/pvs.git/lib/exp2_c.c /Users/e21660/shankar/pvs.git/lib/euclidean_division_c.c /Users/e21660/shankar/pvs.git/lib/real_defs_c.c bv_c.c -lgmp 

struct bv_funtype_0_s;
        typedef struct bv_funtype_0_s * bv_funtype_0_t;

struct bv_funtype_0_ftbl_s {bool_t (* fptr)(struct bv_funtype_0_s *, mpz_ptr_t);
        bool_t (* mptr)(struct bv_funtype_0_s *, mpz_ptr_t);
        void (* rptr)(struct bv_funtype_0_s *);
        struct bv_funtype_0_s * (* cptr)(struct bv_funtype_0_s *);};
typedef struct bv_funtype_0_ftbl_s * bv_funtype_0_ftbl_t;

struct bv_funtype_0_hashentry_s {uint32_t keyhash; mpz_ptr_t key; bool_t value;}; 
typedef struct bv_funtype_0_hashentry_s bv_funtype_0_hashentry_t;

struct bv_funtype_0_htbl_s {uint32_t size; uint32_t num_entries; bv_funtype_0_hashentry_t * data;}; 
typedef struct bv_funtype_0_htbl_s * bv_funtype_0_htbl_t;

struct bv_funtype_0_s {uint32_t count;
        bv_funtype_0_ftbl_t ftbl;
        bv_funtype_0_htbl_t htbl;};
typedef struct bv_funtype_0_s * bv_funtype_0_t;

extern void release_bv_funtype_0(bv_funtype_0_t x, mpz_ptr_t bv__N);

extern bv_funtype_0_t copy_bv_funtype_0(bv_funtype_0_t x);

uint32_t lookup_bv_funtype_0(bv_funtype_0_htbl_t htbl, mpz_ptr_t i, uint32_t ihash);

bv_funtype_0_t dupdate_bv_funtype_0(bv_funtype_0_t a, mpz_ptr_t i, bool_t v, mpz_ptr_t bv__N);

extern bv_funtype_0_t update_bv_funtype_0(bv_funtype_0_t a, mpz_ptr_t i, bool_t v, mpz_ptr_t bv__N);

extern bool_t equal_bv_funtype_0(bv_funtype_0_t x, bv_funtype_0_t y, mpz_ptr_t bv__N);




struct bv_closure_1_s;
        typedef struct bv_closure_1_s * bv_closure_1_t;

struct bv_closure_1_s {uint32_t count;
         bv_funtype_0_ftbl_t ftbl;
         bv_funtype_0_htbl_t htbl;
        bool_t fvar_1;};

bool_t f_bv_closure_1(struct bv_closure_1_s * closure, mpz_ptr_t bvar);

bool_t m_bv_closure_1(struct bv_closure_1_s * closure, mpz_ptr_t bvar);

extern bool_t h_bv_closure_1(mpz_ptr_t ivar_3, bool_t ivar_1);

extern bv_closure_1_t new_bv_closure_1(void);

extern void release_bv_closure_1(bv_funtype_0_t closure, mpz_ptr_t bv__N);

extern bv_closure_1_t copy_bv_closure_1(bv_closure_1_t x);



extern bool_t bv__bvec0(mpz_ptr_t bv__N, mpz_ptr_t ivar_1);

extern bool_t bv__bvec1(mpz_ptr_t bv__N, mpz_ptr_t ivar_1);

extern bv_funtype_0_t bv__fill(mpz_ptr_t bv__N, bool_t ivar_1);

extern bool_t bv__caret(mpz_ptr_t bv__N, bv_funtype_0_t ivar_1, mpz_ptr_t ivar_2);
#endif