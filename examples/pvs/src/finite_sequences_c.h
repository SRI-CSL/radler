//Code generated using pvs2ir
#ifndef _finite_sequences_h 
#define _finite_sequences_h

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

#include "real_defs_c.h"

//cc -O3 -Wall -o finite_sequences -I /Users/e21660/shankar/pvs.git//include /Users/e21660/shankar/pvs.git//lib/pvslib.c  -I /Users/e21660/shankar/pvs.git/lib /Users/e21660/shankar/pvs.git/lib/real_defs_c.c finite_sequences_c.c -lgmp 

typedef pointer_t finite_sequences__T_t;

struct finite_sequences_funtype_0_s;
        typedef struct finite_sequences_funtype_0_s * finite_sequences_funtype_0_t;

struct finite_sequences_funtype_0_ftbl_s {finite_sequences__T_t (* fptr)(struct finite_sequences_funtype_0_s *, mpz_ptr_t);
        finite_sequences__T_t (* mptr)(struct finite_sequences_funtype_0_s *, mpz_ptr_t);
        void (* rptr)(struct finite_sequences_funtype_0_s *);
        struct finite_sequences_funtype_0_s * (* cptr)(struct finite_sequences_funtype_0_s *);};
typedef struct finite_sequences_funtype_0_ftbl_s * finite_sequences_funtype_0_ftbl_t;

struct finite_sequences_funtype_0_hashentry_s {uint32_t keyhash; mpz_ptr_t key; finite_sequences__T_t value;}; 
typedef struct finite_sequences_funtype_0_hashentry_s finite_sequences_funtype_0_hashentry_t;

struct finite_sequences_funtype_0_htbl_s {uint32_t size; uint32_t num_entries; finite_sequences_funtype_0_hashentry_t * data;}; 
typedef struct finite_sequences_funtype_0_htbl_s * finite_sequences_funtype_0_htbl_t;

struct finite_sequences_funtype_0_s {uint32_t count;
        finite_sequences_funtype_0_ftbl_t ftbl;
        finite_sequences_funtype_0_htbl_t htbl;};
typedef struct finite_sequences_funtype_0_s * finite_sequences_funtype_0_t;

extern void release_finite_sequences_funtype_0(finite_sequences_funtype_0_t x, type_actual_t finite_sequences__T);

extern finite_sequences_funtype_0_t copy_finite_sequences_funtype_0(finite_sequences_funtype_0_t x);

uint32_t lookup_finite_sequences_funtype_0(finite_sequences_funtype_0_htbl_t htbl, mpz_ptr_t i, uint32_t ihash);

finite_sequences_funtype_0_t dupdate_finite_sequences_funtype_0(finite_sequences_funtype_0_t a, mpz_ptr_t i, finite_sequences__T_t v, type_actual_t finite_sequences__T);

extern finite_sequences_funtype_0_t update_finite_sequences_funtype_0(finite_sequences_funtype_0_t a, mpz_ptr_t i, finite_sequences__T_t v, type_actual_t finite_sequences__T);

extern bool_t equal_finite_sequences_funtype_0(finite_sequences_funtype_0_t x, finite_sequences_funtype_0_t y, type_actual_t finite_sequences__T);



struct finite_sequences__finseq_s {
        uint32_t count; 
        mpz_t length;
        finite_sequences_funtype_0_t seq;};
typedef struct finite_sequences__finseq_s * finite_sequences__finseq_t;

extern finite_sequences__finseq_t new_finite_sequences__finseq(void);

extern void release_finite_sequences__finseq(finite_sequences__finseq_t x, type_actual_t finite_sequences__T);

extern finite_sequences__finseq_t copy_finite_sequences__finseq(finite_sequences__finseq_t x);

extern bool_t equal_finite_sequences__finseq(finite_sequences__finseq_t x, finite_sequences__finseq_t y, type_actual_t finite_sequences__T);
typedef struct actual_finite_sequences__finseq_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; type_actual_t finite_sequences__T;} * actual_finite_sequences__finseq_t;

void release_finite_sequences__finseq_ptr(pointer_t x, type_actual_t finite_sequences__finseq);
extern bool_t equal_finite_sequences__finseq_ptr(pointer_t x, pointer_t y, actual_finite_sequences__finseq_t T);

actual_finite_sequences__finseq_t actual_finite_sequences__finseq(type_actual_t finite_sequences__T);

extern finite_sequences__finseq_t update_finite_sequences__finseq_length(finite_sequences__finseq_t x, mpz_ptr_t v);

extern finite_sequences__finseq_t update_finite_sequences__finseq_seq(finite_sequences__finseq_t x, finite_sequences_funtype_0_t v, type_actual_t finite_sequences__T);



struct finite_sequences_funtype_2_s;
        typedef struct finite_sequences_funtype_2_s * finite_sequences_funtype_2_t;

struct finite_sequences_funtype_2_ftbl_s {finite_sequences__T_t (* fptr)(struct finite_sequences_funtype_2_s *, uint8_t);
        finite_sequences__T_t (* mptr)(struct finite_sequences_funtype_2_s *, uint8_t);
        void (* rptr)(struct finite_sequences_funtype_2_s *);
        struct finite_sequences_funtype_2_s * (* cptr)(struct finite_sequences_funtype_2_s *);};
typedef struct finite_sequences_funtype_2_ftbl_s * finite_sequences_funtype_2_ftbl_t;

struct finite_sequences_funtype_2_hashentry_s {uint32_t keyhash; uint8_t key; finite_sequences__T_t value;}; 
typedef struct finite_sequences_funtype_2_hashentry_s finite_sequences_funtype_2_hashentry_t;

struct finite_sequences_funtype_2_htbl_s {uint32_t size; uint32_t num_entries; finite_sequences_funtype_2_hashentry_t * data;}; 
typedef struct finite_sequences_funtype_2_htbl_s * finite_sequences_funtype_2_htbl_t;

struct finite_sequences_funtype_2_s {uint32_t count;
        finite_sequences_funtype_2_ftbl_t ftbl;
        finite_sequences_funtype_2_htbl_t htbl;};
typedef struct finite_sequences_funtype_2_s * finite_sequences_funtype_2_t;

extern void release_finite_sequences_funtype_2(finite_sequences_funtype_2_t x, type_actual_t finite_sequences__T);

extern finite_sequences_funtype_2_t copy_finite_sequences_funtype_2(finite_sequences_funtype_2_t x);

uint32_t lookup_finite_sequences_funtype_2(finite_sequences_funtype_2_htbl_t htbl, uint8_t i, uint32_t ihash);

finite_sequences_funtype_2_t dupdate_finite_sequences_funtype_2(finite_sequences_funtype_2_t a, uint8_t i, finite_sequences__T_t v, type_actual_t finite_sequences__T);

extern finite_sequences_funtype_2_t update_finite_sequences_funtype_2(finite_sequences_funtype_2_t a, uint8_t i, finite_sequences__T_t v, type_actual_t finite_sequences__T);

extern bool_t equal_finite_sequences_funtype_2(finite_sequences_funtype_2_t x, finite_sequences_funtype_2_t y, type_actual_t finite_sequences__T);




struct finite_sequences_closure_3_s;
        typedef struct finite_sequences_closure_3_s * finite_sequences_closure_3_t;

struct finite_sequences_closure_3_s {uint32_t count;
         finite_sequences_funtype_2_ftbl_t ftbl;
         finite_sequences_funtype_2_htbl_t htbl;
        type_actual_t fvar_1;};

finite_sequences__T_t f_finite_sequences_closure_3(struct finite_sequences_closure_3_s * closure, uint8_t bvar);

finite_sequences__T_t m_finite_sequences_closure_3(struct finite_sequences_closure_3_s * closure, uint8_t bvar);

extern finite_sequences__T_t h_finite_sequences_closure_3(uint8_t ivar_4, type_actual_t finite_sequences__T);

extern finite_sequences_closure_3_t new_finite_sequences_closure_3(void);

extern void release_finite_sequences_closure_3(finite_sequences_funtype_2_t closure, type_actual_t finite_sequences__T);

extern finite_sequences_closure_3_t copy_finite_sequences_closure_3(finite_sequences_closure_3_t x);




struct finite_sequences_closure_4_s;
        typedef struct finite_sequences_closure_4_s * finite_sequences_closure_4_t;

struct finite_sequences_closure_4_s {uint32_t count;
         finite_sequences_funtype_0_ftbl_t ftbl;
         finite_sequences_funtype_0_htbl_t htbl;
        finite_sequences_funtype_2_t fvar_1;
        type_actual_t fvar_2;};

finite_sequences__T_t f_finite_sequences_closure_4(struct finite_sequences_closure_4_s * closure, mpz_ptr_t bvar);

finite_sequences__T_t m_finite_sequences_closure_4(struct finite_sequences_closure_4_s * closure, mpz_ptr_t bvar);

extern finite_sequences__T_t h_finite_sequences_closure_4(mpz_ptr_t ivar_15, finite_sequences_funtype_2_t ivar_12, type_actual_t finite_sequences__T);

extern finite_sequences_closure_4_t new_finite_sequences_closure_4(void);

extern void release_finite_sequences_closure_4(finite_sequences_funtype_0_t closure, type_actual_t finite_sequences__T);

extern finite_sequences_closure_4_t copy_finite_sequences_closure_4(finite_sequences_closure_4_t x);




struct finite_sequences_closure_5_s;
        typedef struct finite_sequences_closure_5_s * finite_sequences_closure_5_t;

struct finite_sequences_closure_5_s {uint32_t count;
         finite_sequences_funtype_0_ftbl_t ftbl;
         finite_sequences_funtype_0_htbl_t htbl;
        mpz_t fvar_1;
        type_actual_t fvar_2;
        finite_sequences__finseq_t fvar_3;
        finite_sequences__finseq_t fvar_4;};

finite_sequences__T_t f_finite_sequences_closure_5(struct finite_sequences_closure_5_s * closure, mpz_ptr_t bvar);

finite_sequences__T_t m_finite_sequences_closure_5(struct finite_sequences_closure_5_s * closure, mpz_ptr_t bvar);

extern finite_sequences__T_t h_finite_sequences_closure_5(mpz_ptr_t ivar_13, mpz_ptr_t ivar_3, type_actual_t finite_sequences__T, finite_sequences__finseq_t ivar_2, finite_sequences__finseq_t ivar_1);

extern finite_sequences_closure_5_t new_finite_sequences_closure_5(void);

extern void release_finite_sequences_closure_5(finite_sequences_funtype_0_t closure, type_actual_t finite_sequences__T);

extern finite_sequences_closure_5_t copy_finite_sequences_closure_5(finite_sequences_closure_5_t x);



struct finite_sequences_record_6_s {
        uint32_t count; 
        mpz_t project_1;
        mpz_t project_2;};
typedef struct finite_sequences_record_6_s * finite_sequences_record_6_t;

extern finite_sequences_record_6_t new_finite_sequences_record_6(void);

extern void release_finite_sequences_record_6(finite_sequences_record_6_t x, type_actual_t finite_sequences__T);

extern finite_sequences_record_6_t copy_finite_sequences_record_6(finite_sequences_record_6_t x);

extern bool_t equal_finite_sequences_record_6(finite_sequences_record_6_t x, finite_sequences_record_6_t y, type_actual_t finite_sequences__T);
typedef struct actual_finite_sequences_record_6_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr; type_actual_t finite_sequences__T;} * actual_finite_sequences_record_6_t;

void release_finite_sequences_record_6_ptr(pointer_t x, type_actual_t finite_sequences_record_6);
extern bool_t equal_finite_sequences_record_6_ptr(pointer_t x, pointer_t y, actual_finite_sequences_record_6_t T);

actual_finite_sequences_record_6_t actual_finite_sequences_record_6(type_actual_t finite_sequences__T);

extern finite_sequences_record_6_t update_finite_sequences_record_6_project_1(finite_sequences_record_6_t x, mpz_ptr_t v);

extern finite_sequences_record_6_t update_finite_sequences_record_6_project_2(finite_sequences_record_6_t x, mpz_ptr_t v);




struct finite_sequences_closure_7_s;
        typedef struct finite_sequences_closure_7_s * finite_sequences_closure_7_t;

struct finite_sequences_closure_7_s {uint32_t count;
         finite_sequences_funtype_0_ftbl_t ftbl;
         finite_sequences_funtype_0_htbl_t htbl;
        mpz_t fvar_1;
        type_actual_t fvar_2;
        finite_sequences__finseq_t fvar_3;};

finite_sequences__T_t f_finite_sequences_closure_7(struct finite_sequences_closure_7_s * closure, mpz_ptr_t bvar);

finite_sequences__T_t m_finite_sequences_closure_7(struct finite_sequences_closure_7_s * closure, mpz_ptr_t bvar);

extern finite_sequences__T_t h_finite_sequences_closure_7(mpz_ptr_t ivar_42, mpz_ptr_t ivar_3, type_actual_t finite_sequences__T, finite_sequences__finseq_t ivar_1);

extern finite_sequences_closure_7_t new_finite_sequences_closure_7(void);

extern void release_finite_sequences_closure_7(finite_sequences_funtype_0_t closure, type_actual_t finite_sequences__T);

extern finite_sequences_closure_7_t copy_finite_sequences_closure_7(finite_sequences_closure_7_t x);




struct finite_sequences_closure_8_s;
        typedef struct finite_sequences_closure_8_s * finite_sequences_closure_8_t;

struct finite_sequences_closure_8_s {uint32_t count;
         finite_sequences_funtype_0_ftbl_t ftbl;
         finite_sequences_funtype_0_htbl_t htbl;
        mpz_t fvar_1;
        type_actual_t fvar_2;
        finite_sequences__finseq_t fvar_3;};

finite_sequences__T_t f_finite_sequences_closure_8(struct finite_sequences_closure_8_s * closure, mpz_ptr_t bvar);

finite_sequences__T_t m_finite_sequences_closure_8(struct finite_sequences_closure_8_s * closure, mpz_ptr_t bvar);

extern finite_sequences__T_t h_finite_sequences_closure_8(mpz_ptr_t ivar_39, mpz_ptr_t ivar_3, type_actual_t finite_sequences__T, finite_sequences__finseq_t ivar_1);

extern finite_sequences_closure_8_t new_finite_sequences_closure_8(void);

extern void release_finite_sequences_closure_8(finite_sequences_funtype_0_t closure, type_actual_t finite_sequences__T);

extern finite_sequences_closure_8_t copy_finite_sequences_closure_8(finite_sequences_closure_8_t x);



extern finite_sequences__finseq_t finite_sequences__empty_seq(type_actual_t finite_sequences__T);

extern finite_sequences_funtype_0_t finite_sequences__finseq_appl(type_actual_t finite_sequences__T, finite_sequences__finseq_t ivar_1);

extern finite_sequences__finseq_t finite_sequences__oh(type_actual_t finite_sequences__T, finite_sequences__finseq_t ivar_1, finite_sequences__finseq_t ivar_2);

extern finite_sequences__finseq_t finite_sequences__caret(type_actual_t finite_sequences__T, finite_sequences__finseq_t ivar_1, finite_sequences_record_6_t ivar_2);

extern finite_sequences__finseq_t finite_sequences__doublecaret(type_actual_t finite_sequences__T, finite_sequences__finseq_t ivar_1, finite_sequences_record_6_t ivar_2);

extern finite_sequences__T_t finite_sequences__extract1(type_actual_t finite_sequences__T, finite_sequences__finseq_t ivar_1);
#endif