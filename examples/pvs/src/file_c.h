//Code generated using pvs2ir
#ifndef _file_h 
#define _file_h

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

#include "integertypes_c.h"

#include "exp2_c.h"

#include "euclidean_division_c.h"

#include "real_defs_c.h"

//cc -O3 -Wall -o file -I /Users/e21660/shankar/pvs.git//include /Users/e21660/shankar/pvs.git//lib/pvslib.c  -I /Users/e21660/shankar/pvs.git/lib /Users/e21660/shankar/pvs.git/lib/bytestrings_c.c /Users/e21660/shankar/pvs.git/lib/gen_strings_c.c /Users/e21660/shankar/pvs.git/lib/strings_c.c /Users/e21660/shankar/pvs.git/lib/ordinals_c.c /Users/e21660/shankar/pvs.git/lib/ordstruct_adt_c.c /Users/e21660/shankar/pvs.git/lib/integertypes_c.c /Users/e21660/shankar/pvs.git/lib/exp2_c.c /Users/e21660/shankar/pvs.git/lib/euclidean_division_c.c /Users/e21660/shankar/pvs.git/lib/real_defs_c.c file_c.c -lgmp 

typedef file_t file__file_t;



struct file__lifted_file_adt_s {
         uint32_t count; 
        uint8_t file__lifted_file_adt_index;};
typedef struct file__lifted_file_adt_s * file__lifted_file_adt_t;

extern file__lifted_file_adt_t new_file__lifted_file_adt(void);

extern void release_file__lifted_file_adt(file__lifted_file_adt_t x);

extern file__lifted_file_adt_t copy_file__lifted_file_adt(file__lifted_file_adt_t x);

extern bool_t equal_file__lifted_file_adt(file__lifted_file_adt_t x, file__lifted_file_adt_t y);
typedef struct actual_file__lifted_file_adt_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr;} * actual_file__lifted_file_adt_t;

void release_file__lifted_file_adt_ptr(pointer_t x, type_actual_t file__lifted_file_adt);
extern bool_t equal_file__lifted_file_adt_ptr(pointer_t x, pointer_t y, actual_file__lifted_file_adt_t T);

actual_file__lifted_file_adt_t actual_file__lifted_file_adt(void);

extern file__lifted_file_adt_t update_file__lifted_file_adt_file__lifted_file_adt_index(file__lifted_file_adt_t x, uint8_t v);



struct file__pass_s {
        uint32_t count; 
        uint8_t file__lifted_file_adt_index;
        file__file_t contents;};
typedef struct file__pass_s * file__pass_t;

extern file__pass_t new_file__pass(void);

extern void release_file__pass(file__pass_t x);

extern file__pass_t copy_file__pass(file__pass_t x);

extern bool_t equal_file__pass(file__pass_t x, file__pass_t y);
typedef struct actual_file__pass_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr;} * actual_file__pass_t;

void release_file__pass_ptr(pointer_t x, type_actual_t file__pass);
extern bool_t equal_file__pass_ptr(pointer_t x, pointer_t y, actual_file__pass_t T);

actual_file__pass_t actual_file__pass(void);

extern file__pass_t update_file__pass_file__lifted_file_adt_index(file__pass_t x, uint8_t v);

extern file__pass_t update_file__pass_contents(file__pass_t x, file__file_t v);



struct file_funtype_3_s;
        typedef struct file_funtype_3_s * file_funtype_3_t;

struct file_funtype_3_ftbl_s {uint8_t (* fptr)(struct file_funtype_3_s *, file__lifted_file_adt_t);
        uint8_t (* mptr)(struct file_funtype_3_s *, file__lifted_file_adt_t);
        void (* rptr)(struct file_funtype_3_s *);
        struct file_funtype_3_s * (* cptr)(struct file_funtype_3_s *);};
typedef struct file_funtype_3_ftbl_s * file_funtype_3_ftbl_t;

struct file_funtype_3_hashentry_s {uint32_t keyhash; file__lifted_file_adt_t key; uint8_t value;}; 
typedef struct file_funtype_3_hashentry_s file_funtype_3_hashentry_t;

struct file_funtype_3_htbl_s {uint32_t size; uint32_t num_entries; file_funtype_3_hashentry_t * data;}; 
typedef struct file_funtype_3_htbl_s * file_funtype_3_htbl_t;

struct file_funtype_3_s {uint32_t count;
        file_funtype_3_ftbl_t ftbl;
        file_funtype_3_htbl_t htbl;};
typedef struct file_funtype_3_s * file_funtype_3_t;

extern void release_file_funtype_3(file_funtype_3_t x);

extern file_funtype_3_t copy_file_funtype_3(file_funtype_3_t x);

extern bool_t equal_file_funtype_3(file_funtype_3_t x, file_funtype_3_t y);



struct file_funtype_4_s;
        typedef struct file_funtype_4_s * file_funtype_4_t;

struct file_funtype_4_ftbl_s {mpz_ptr_t (* fptr)(struct file_funtype_4_s *, file__lifted_file_adt_t);
        mpz_ptr_t (* mptr)(struct file_funtype_4_s *, file__lifted_file_adt_t);
        void (* rptr)(struct file_funtype_4_s *);
        struct file_funtype_4_s * (* cptr)(struct file_funtype_4_s *);};
typedef struct file_funtype_4_ftbl_s * file_funtype_4_ftbl_t;

struct file_funtype_4_hashentry_s {uint32_t keyhash; file__lifted_file_adt_t key; mpz_t value;}; 
typedef struct file_funtype_4_hashentry_s file_funtype_4_hashentry_t;

struct file_funtype_4_htbl_s {uint32_t size; uint32_t num_entries; file_funtype_4_hashentry_t * data;}; 
typedef struct file_funtype_4_htbl_s * file_funtype_4_htbl_t;

struct file_funtype_4_s {uint32_t count;
        file_funtype_4_ftbl_t ftbl;
        file_funtype_4_htbl_t htbl;};
typedef struct file_funtype_4_s * file_funtype_4_t;

extern void release_file_funtype_4(file_funtype_4_t x);

extern file_funtype_4_t copy_file_funtype_4(file_funtype_4_t x);

extern bool_t equal_file_funtype_4(file_funtype_4_t x, file_funtype_4_t y);



struct file_funtype_5_s;
        typedef struct file_funtype_5_s * file_funtype_5_t;

struct file_funtype_5_ftbl_s {mpz_ptr_t (* fptr)(struct file_funtype_5_s *, file__file_t);
        mpz_ptr_t (* mptr)(struct file_funtype_5_s *, file__file_t);
        void (* rptr)(struct file_funtype_5_s *);
        struct file_funtype_5_s * (* cptr)(struct file_funtype_5_s *);};
typedef struct file_funtype_5_ftbl_s * file_funtype_5_ftbl_t;

struct file_funtype_5_hashentry_s {uint32_t keyhash; file__file_t key; mpz_t value;}; 
typedef struct file_funtype_5_hashentry_s file_funtype_5_hashentry_t;

struct file_funtype_5_htbl_s {uint32_t size; uint32_t num_entries; file_funtype_5_hashentry_t * data;}; 
typedef struct file_funtype_5_htbl_s * file_funtype_5_htbl_t;

struct file_funtype_5_s {uint32_t count;
        file_funtype_5_ftbl_t ftbl;
        file_funtype_5_htbl_t htbl;};
typedef struct file_funtype_5_s * file_funtype_5_t;

extern void release_file_funtype_5(file_funtype_5_t x);

extern file_funtype_5_t copy_file_funtype_5(file_funtype_5_t x);

extern bool_t equal_file_funtype_5(file_funtype_5_t x, file_funtype_5_t y);




struct file_closure_6_s;
        typedef struct file_closure_6_s * file_closure_6_t;

struct file_closure_6_s {uint32_t count;
         file_funtype_4_ftbl_t ftbl;
         file_funtype_4_htbl_t htbl;
        file_funtype_5_t fvar_1;
        mpz_t fvar_2;};

mpz_ptr_t f_file_closure_6(struct file_closure_6_s * closure, file__lifted_file_adt_t bvar);

mpz_ptr_t m_file_closure_6(struct file_closure_6_s * closure, file__lifted_file_adt_t bvar);

extern mpz_ptr_t h_file_closure_6(file__lifted_file_adt_t ivar_9, file_funtype_5_t ivar_5, mpz_ptr_t ivar_4);

extern file_closure_6_t new_file_closure_6(void);

extern void release_file_closure_6(file_funtype_4_t closure);

extern file_closure_6_t copy_file_closure_6(file_closure_6_t x);



struct file_record_7_s {
        uint32_t count; 
        file__file_t project_1;
        file__lifted_file_adt_t project_2;};
typedef struct file_record_7_s * file_record_7_t;

extern file_record_7_t new_file_record_7(void);

extern void release_file_record_7(file_record_7_t x);

extern file_record_7_t copy_file_record_7(file_record_7_t x);

extern bool_t equal_file_record_7(file_record_7_t x, file_record_7_t y);
typedef struct actual_file_record_7_s {equal_ptr_t equal_ptr; release_ptr_t release_ptr;} * actual_file_record_7_t;

void release_file_record_7_ptr(pointer_t x, type_actual_t file_record_7);
extern bool_t equal_file_record_7_ptr(pointer_t x, pointer_t y, actual_file_record_7_t T);

actual_file_record_7_t actual_file_record_7(void);

extern file_record_7_t update_file_record_7_project_1(file_record_7_t x, file__file_t v);

extern file_record_7_t update_file_record_7_project_2(file_record_7_t x, file__lifted_file_adt_t v);



struct file_funtype_8_s;
        typedef struct file_funtype_8_s * file_funtype_8_t;

struct file_funtype_8_ftbl_s {mpz_ptr_t (* fptr)(struct file_funtype_8_s *, file_record_7_t);
        mpz_ptr_t (* mptr)(struct file_funtype_8_s *, file__file_t, file__lifted_file_adt_t);
        void (* rptr)(struct file_funtype_8_s *);
        struct file_funtype_8_s * (* cptr)(struct file_funtype_8_s *);};
typedef struct file_funtype_8_ftbl_s * file_funtype_8_ftbl_t;

struct file_funtype_8_hashentry_s {uint32_t keyhash; file_record_7_t key; mpz_t value;}; 
typedef struct file_funtype_8_hashentry_s file_funtype_8_hashentry_t;

struct file_funtype_8_htbl_s {uint32_t size; uint32_t num_entries; file_funtype_8_hashentry_t * data;}; 
typedef struct file_funtype_8_htbl_s * file_funtype_8_htbl_t;

struct file_funtype_8_s {uint32_t count;
        file_funtype_8_ftbl_t ftbl;
        file_funtype_8_htbl_t htbl;};
typedef struct file_funtype_8_s * file_funtype_8_t;

extern void release_file_funtype_8(file_funtype_8_t x);

extern file_funtype_8_t copy_file_funtype_8(file_funtype_8_t x);

extern bool_t equal_file_funtype_8(file_funtype_8_t x, file_funtype_8_t y);




struct file_closure_9_s;
        typedef struct file_closure_9_s * file_closure_9_t;

struct file_closure_9_s {uint32_t count;
         file_funtype_4_ftbl_t ftbl;
         file_funtype_4_htbl_t htbl;
        file_funtype_4_t fvar_1;
        file_funtype_8_t fvar_2;};

mpz_ptr_t f_file_closure_9(struct file_closure_9_s * closure, file__lifted_file_adt_t bvar);

mpz_ptr_t m_file_closure_9(struct file_closure_9_s * closure, file__lifted_file_adt_t bvar);

extern mpz_ptr_t h_file_closure_9(file__lifted_file_adt_t ivar_11, file_funtype_4_t ivar_5, file_funtype_8_t ivar_7);

extern file_closure_9_t new_file_closure_9(void);

extern void release_file_closure_9(file_funtype_4_t closure);

extern file_closure_9_t copy_file_closure_9(file_closure_9_t x);



struct file_funtype_10_s;
        typedef struct file_funtype_10_s * file_funtype_10_t;

struct file_funtype_10_ftbl_s {ordstruct_adt__ordstruct_adt_t (* fptr)(struct file_funtype_10_s *, file__lifted_file_adt_t);
        ordstruct_adt__ordstruct_adt_t (* mptr)(struct file_funtype_10_s *, file__lifted_file_adt_t);
        void (* rptr)(struct file_funtype_10_s *);
        struct file_funtype_10_s * (* cptr)(struct file_funtype_10_s *);};
typedef struct file_funtype_10_ftbl_s * file_funtype_10_ftbl_t;

struct file_funtype_10_hashentry_s {uint32_t keyhash; file__lifted_file_adt_t key; ordstruct_adt__ordstruct_adt_t value;}; 
typedef struct file_funtype_10_hashentry_s file_funtype_10_hashentry_t;

struct file_funtype_10_htbl_s {uint32_t size; uint32_t num_entries; file_funtype_10_hashentry_t * data;}; 
typedef struct file_funtype_10_htbl_s * file_funtype_10_htbl_t;

struct file_funtype_10_s {uint32_t count;
        file_funtype_10_ftbl_t ftbl;
        file_funtype_10_htbl_t htbl;};
typedef struct file_funtype_10_s * file_funtype_10_t;

extern void release_file_funtype_10(file_funtype_10_t x);

extern file_funtype_10_t copy_file_funtype_10(file_funtype_10_t x);

extern bool_t equal_file_funtype_10(file_funtype_10_t x, file_funtype_10_t y);



struct file_funtype_11_s;
        typedef struct file_funtype_11_s * file_funtype_11_t;

struct file_funtype_11_ftbl_s {ordstruct_adt__ordstruct_adt_t (* fptr)(struct file_funtype_11_s *, file__file_t);
        ordstruct_adt__ordstruct_adt_t (* mptr)(struct file_funtype_11_s *, file__file_t);
        void (* rptr)(struct file_funtype_11_s *);
        struct file_funtype_11_s * (* cptr)(struct file_funtype_11_s *);};
typedef struct file_funtype_11_ftbl_s * file_funtype_11_ftbl_t;

struct file_funtype_11_hashentry_s {uint32_t keyhash; file__file_t key; ordstruct_adt__ordstruct_adt_t value;}; 
typedef struct file_funtype_11_hashentry_s file_funtype_11_hashentry_t;

struct file_funtype_11_htbl_s {uint32_t size; uint32_t num_entries; file_funtype_11_hashentry_t * data;}; 
typedef struct file_funtype_11_htbl_s * file_funtype_11_htbl_t;

struct file_funtype_11_s {uint32_t count;
        file_funtype_11_ftbl_t ftbl;
        file_funtype_11_htbl_t htbl;};
typedef struct file_funtype_11_s * file_funtype_11_t;

extern void release_file_funtype_11(file_funtype_11_t x);

extern file_funtype_11_t copy_file_funtype_11(file_funtype_11_t x);

extern bool_t equal_file_funtype_11(file_funtype_11_t x, file_funtype_11_t y);




struct file_closure_12_s;
        typedef struct file_closure_12_s * file_closure_12_t;

struct file_closure_12_s {uint32_t count;
         file_funtype_10_ftbl_t ftbl;
         file_funtype_10_htbl_t htbl;
        file_funtype_11_t fvar_1;
        ordstruct_adt__ordstruct_adt_t fvar_2;};

ordstruct_adt__ordstruct_adt_t f_file_closure_12(struct file_closure_12_s * closure, file__lifted_file_adt_t bvar);

ordstruct_adt__ordstruct_adt_t m_file_closure_12(struct file_closure_12_s * closure, file__lifted_file_adt_t bvar);

extern ordstruct_adt__ordstruct_adt_t h_file_closure_12(file__lifted_file_adt_t ivar_9, file_funtype_11_t ivar_5, ordstruct_adt__ordstruct_adt_t ivar_4);

extern file_closure_12_t new_file_closure_12(void);

extern void release_file_closure_12(file_funtype_10_t closure);

extern file_closure_12_t copy_file_closure_12(file_closure_12_t x);



struct file_funtype_13_s;
        typedef struct file_funtype_13_s * file_funtype_13_t;

struct file_funtype_13_ftbl_s {ordstruct_adt__ordstruct_adt_t (* fptr)(struct file_funtype_13_s *, file_record_7_t);
        ordstruct_adt__ordstruct_adt_t (* mptr)(struct file_funtype_13_s *, file__file_t, file__lifted_file_adt_t);
        void (* rptr)(struct file_funtype_13_s *);
        struct file_funtype_13_s * (* cptr)(struct file_funtype_13_s *);};
typedef struct file_funtype_13_ftbl_s * file_funtype_13_ftbl_t;

struct file_funtype_13_hashentry_s {uint32_t keyhash; file_record_7_t key; ordstruct_adt__ordstruct_adt_t value;}; 
typedef struct file_funtype_13_hashentry_s file_funtype_13_hashentry_t;

struct file_funtype_13_htbl_s {uint32_t size; uint32_t num_entries; file_funtype_13_hashentry_t * data;}; 
typedef struct file_funtype_13_htbl_s * file_funtype_13_htbl_t;

struct file_funtype_13_s {uint32_t count;
        file_funtype_13_ftbl_t ftbl;
        file_funtype_13_htbl_t htbl;};
typedef struct file_funtype_13_s * file_funtype_13_t;

extern void release_file_funtype_13(file_funtype_13_t x);

extern file_funtype_13_t copy_file_funtype_13(file_funtype_13_t x);

extern bool_t equal_file_funtype_13(file_funtype_13_t x, file_funtype_13_t y);




struct file_closure_14_s;
        typedef struct file_closure_14_s * file_closure_14_t;

struct file_closure_14_s {uint32_t count;
         file_funtype_10_ftbl_t ftbl;
         file_funtype_10_htbl_t htbl;
        file_funtype_10_t fvar_1;
        file_funtype_13_t fvar_2;};

ordstruct_adt__ordstruct_adt_t f_file_closure_14(struct file_closure_14_s * closure, file__lifted_file_adt_t bvar);

ordstruct_adt__ordstruct_adt_t m_file_closure_14(struct file_closure_14_s * closure, file__lifted_file_adt_t bvar);

extern ordstruct_adt__ordstruct_adt_t h_file_closure_14(file__lifted_file_adt_t ivar_11, file_funtype_10_t ivar_5, file_funtype_13_t ivar_7);

extern file_closure_14_t new_file_closure_14(void);

extern void release_file_closure_14(file_funtype_10_t closure);

extern file_closure_14_t copy_file_closure_14(file_closure_14_t x);



extern int32_t file__max_file_size(void);

extern bool_t r_file__failp(file__lifted_file_adt_t ivar_1);

extern bool_t r_file__passp(file__lifted_file_adt_t ivar_1);

extern file__pass_t update_file__lifted_file_adt_contents(file__lifted_file_adt_t ivar_1, file__file_t ivar_3);

extern file__file_t file__lifted_file_adt_contents(file__lifted_file_adt_t ivar_1);

extern file__lifted_file_adt_t file__fail(void);

extern file__lifted_file_adt_t file__pass(file__file_t ivar_2);

extern file_funtype_3_t file__lifted_file_ord(void);

extern uint8_t file__ord(file__lifted_file_adt_t ivar_2);

extern bool_t file__subterm(file__lifted_file_adt_t ivar_1, file__lifted_file_adt_t ivar_2);

extern bool_t file__doublelessp(file__lifted_file_adt_t ivar_1, file__lifted_file_adt_t ivar_2);

extern file_funtype_4_t file__reduce_nat(mpz_ptr_t ivar_4, file_funtype_5_t ivar_5);

extern file_funtype_4_t file__REDUCE_nat(file_funtype_4_t ivar_5, file_funtype_8_t ivar_7);

extern file_funtype_10_t file__reduce_ordinal(ordstruct_adt__ordstruct_adt_t ivar_4, file_funtype_11_t ivar_5);

extern file_funtype_10_t file__REDUCE_ordinal(file_funtype_10_t ivar_5, file_funtype_13_t ivar_7);

extern bool_t file__openp(file__file_t f);

extern file__lifted_file_adt_t file__open(bytestrings__bytestring_t name);

extern file__lifted_file_adt_t file__append(file__file_t f, bytestrings__bytestring_t b);

extern uint32_t file__file_size(file__file_t f);

extern uint8_t file__getbyte(file__file_t f, uint32_t i);

extern bytestrings__bytestring_t file__getbytestring(file__file_t f, uint32_t i, uint32_t size);

extern file__file_t file__setbyte(file__file_t f, uint32_t i, uint8_t b);

extern bytestrings__bytestring_t file__printc(bytestrings__bytestring_t b);

extern bytestrings__bytestring_t file__printh(bytestrings__bytestring_t b);
#endif