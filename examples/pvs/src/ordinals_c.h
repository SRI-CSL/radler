//Code generated using pvs2ir
#ifndef _ordinals_h 
#define _ordinals_h

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

#include "ordstruct_adt_c.h"

//cc -O3 -Wall -o ordinals -I /Users/e21660/shankar/pvs.git//include /Users/e21660/shankar/pvs.git//lib/pvslib.c  -I /Users/e21660/shankar/pvs.git/lib /Users/e21660/shankar/pvs.git/lib/ordstruct_adt_c.c ordinals_c.c -lgmp 

struct ordinals_funtype_0_s;
        typedef struct ordinals_funtype_0_s * ordinals_funtype_0_t;

struct ordinals_funtype_0_ftbl_s {mpz_ptr_t (* fptr)(struct ordinals_funtype_0_s *, ordstruct_adt__ordstruct_adt_t);
        mpz_ptr_t (* mptr)(struct ordinals_funtype_0_s *, ordstruct_adt__ordstruct_adt_t);
        void (* rptr)(struct ordinals_funtype_0_s *);
        struct ordinals_funtype_0_s * (* cptr)(struct ordinals_funtype_0_s *);};
typedef struct ordinals_funtype_0_ftbl_s * ordinals_funtype_0_ftbl_t;

struct ordinals_funtype_0_hashentry_s {uint32_t keyhash; ordstruct_adt__ordstruct_adt_t key; mpz_t value;}; 
typedef struct ordinals_funtype_0_hashentry_s ordinals_funtype_0_hashentry_t;

struct ordinals_funtype_0_htbl_s {uint32_t size; uint32_t num_entries; ordinals_funtype_0_hashentry_t * data;}; 
typedef struct ordinals_funtype_0_htbl_s * ordinals_funtype_0_htbl_t;

struct ordinals_funtype_0_s {uint32_t count;
        ordinals_funtype_0_ftbl_t ftbl;
        ordinals_funtype_0_htbl_t htbl;};
typedef struct ordinals_funtype_0_s * ordinals_funtype_0_t;

extern void release_ordinals_funtype_0(ordinals_funtype_0_t x);

extern ordinals_funtype_0_t copy_ordinals_funtype_0(ordinals_funtype_0_t x);

extern bool_t equal_ordinals_funtype_0(ordinals_funtype_0_t x, ordinals_funtype_0_t y);



struct ordinals_record_1_s {
        uint32_t count; 
        mpz_t project_1;
        mpz_t project_2;
        mpz_t project_3;};
typedef struct ordinals_record_1_s * ordinals_record_1_t;

extern ordinals_record_1_t new_ordinals_record_1(void);

extern void release_ordinals_record_1(ordinals_record_1_t x);

extern ordinals_record_1_t copy_ordinals_record_1(ordinals_record_1_t x);

extern bool_t equal_ordinals_record_1(ordinals_record_1_t x, ordinals_record_1_t y);
typedef struct actual_ordinals_record_1_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr;} * actual_ordinals_record_1_t;

void release_ordinals_record_1_ptr(pointer_t x, type_actual_t ordinals_record_1);
extern bool_t equal_ordinals_record_1_ptr(pointer_t x, pointer_t y, actual_ordinals_record_1_t T);

actual_ordinals_record_1_t actual_ordinals_record_1(void);

extern ordinals_record_1_t update_ordinals_record_1_project_1(ordinals_record_1_t x, mpz_ptr_t v);

extern ordinals_record_1_t update_ordinals_record_1_project_2(ordinals_record_1_t x, mpz_ptr_t v);

extern ordinals_record_1_t update_ordinals_record_1_project_3(ordinals_record_1_t x, mpz_ptr_t v);



struct ordinals_funtype_2_s;
        typedef struct ordinals_funtype_2_s * ordinals_funtype_2_t;

struct ordinals_funtype_2_ftbl_s {mpz_ptr_t (* fptr)(struct ordinals_funtype_2_s *, ordinals_record_1_t);
        mpz_ptr_t (* mptr)(struct ordinals_funtype_2_s *, mpz_ptr_t, mpz_ptr_t, mpz_ptr_t);
        void (* rptr)(struct ordinals_funtype_2_s *);
        struct ordinals_funtype_2_s * (* cptr)(struct ordinals_funtype_2_s *);};
typedef struct ordinals_funtype_2_ftbl_s * ordinals_funtype_2_ftbl_t;

struct ordinals_funtype_2_hashentry_s {uint32_t keyhash; ordinals_record_1_t key; mpz_t value;}; 
typedef struct ordinals_funtype_2_hashentry_s ordinals_funtype_2_hashentry_t;

struct ordinals_funtype_2_htbl_s {uint32_t size; uint32_t num_entries; ordinals_funtype_2_hashentry_t * data;}; 
typedef struct ordinals_funtype_2_htbl_s * ordinals_funtype_2_htbl_t;

struct ordinals_funtype_2_s {uint32_t count;
        ordinals_funtype_2_ftbl_t ftbl;
        ordinals_funtype_2_htbl_t htbl;};
typedef struct ordinals_funtype_2_s * ordinals_funtype_2_t;

extern void release_ordinals_funtype_2(ordinals_funtype_2_t x);

extern ordinals_funtype_2_t copy_ordinals_funtype_2(ordinals_funtype_2_t x);

extern bool_t equal_ordinals_funtype_2(ordinals_funtype_2_t x, ordinals_funtype_2_t y);




struct ordinals_closure_3_s;
        typedef struct ordinals_closure_3_s * ordinals_closure_3_t;

struct ordinals_closure_3_s {uint32_t count;
         ordinals_funtype_2_ftbl_t ftbl;
         ordinals_funtype_2_htbl_t htbl;};

mpz_ptr_t f_ordinals_closure_3(struct ordinals_closure_3_s * closure, ordinals_record_1_t bvar);

mpz_ptr_t m_ordinals_closure_3(struct ordinals_closure_3_s * closure, mpz_ptr_t bvar_1, mpz_ptr_t bvar_2, mpz_ptr_t bvar_3);

extern mpz_ptr_t h_ordinals_closure_3(mpz_ptr_t ivar_4, mpz_ptr_t ivar_5, mpz_ptr_t ivar_6);

extern ordinals_closure_3_t new_ordinals_closure_3(void);

extern void release_ordinals_closure_3(ordinals_funtype_2_t closure);

extern ordinals_closure_3_t copy_ordinals_closure_3(ordinals_closure_3_t x);



extern ordinals_funtype_0_t ordinals__size(void);

extern bool_t ordinals__lessp(ordstruct_adt__ordstruct_adt_t ivar_1, ordstruct_adt__ordstruct_adt_t ivar_2);

extern bool_t ordinals__greaterp(ordstruct_adt__ordstruct_adt_t ivar_1, ordstruct_adt__ordstruct_adt_t ivar_2);

extern bool_t ordinals__lesseqp(ordstruct_adt__ordstruct_adt_t ivar_1, ordstruct_adt__ordstruct_adt_t ivar_2);

extern bool_t ordinals__greatereqp(ordstruct_adt__ordstruct_adt_t ivar_1, ordstruct_adt__ordstruct_adt_t ivar_2);

extern bool_t ordinals__ordinalp(ordstruct_adt__ordstruct_adt_t ivar_1);
#endif