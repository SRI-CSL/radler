//Code generated using pvs2ir
#ifndef _integertypes_h 
#define _integertypes_h

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

#include "exp2_c.h"

#include "euclidean_division_c.h"

#include "real_defs_c.h"

//cc -O3 -Wall -o integertypes -I /Users/e21660/shankar/pvs.git//include /Users/e21660/shankar/pvs.git//lib/pvslib.c  -I /Users/e21660/shankar/pvs.git/lib /Users/e21660/shankar/pvs.git/lib/exp2_c.c /Users/e21660/shankar/pvs.git/lib/euclidean_division_c.c /Users/e21660/shankar/pvs.git/lib/real_defs_c.c integertypes_c.c -lgmp 

extern uint8_t integertypes__max8(void);

extern uint16_t integertypes__max16(void);

extern uint32_t integertypes__max32(void);

extern uint64_t integertypes__max64(void);

extern int8_t integertypes__mini8(void);

extern int16_t integertypes__mini16(void);

extern int32_t integertypes__mini32(void);

extern int64_t integertypes__mini64(void);

extern int8_t integertypes__maxi8(void);

extern int16_t integertypes__maxi16(void);

extern int32_t integertypes__maxi32(void);

extern int64_t integertypes__maxi64(void);

extern uint32_t integertypes__maxindex(void);

static inline uint8_t integertypes__u8plus(uint8_t x, uint8_t y){return (uint8_t)(x + y);}

static inline uint16_t integertypes__u16plus(uint16_t x, uint16_t y){return (uint16_t)(x + y);}

static inline uint32_t integertypes__u32plus(uint32_t x, uint32_t y){return (uint32_t)(x + y);}

static inline uint64_t integertypes__u64plus(uint64_t x, uint64_t y){return (uint64_t)(x + y);}

static inline uint8_t integertypes__u8minus(uint8_t x, uint8_t y){return (uint8_t)(x - y);}

static inline uint16_t integertypes__u16minus(uint16_t x, uint16_t y){return (uint16_t)(x - y);}

static inline uint32_t integertypes__u32minus(uint32_t x, uint32_t y){return (uint32_t)(x - y);}

static inline uint64_t integertypes__u64minus(uint64_t x, uint64_t y){return (uint64_t)(x - y);}

static inline uint8_t integertypes__u8pow2(uint8_t x){return (uint8_t)1<<x;}

static inline uint16_t integertypes__u16pow2(uint16_t x){return (uint16_t)1<<x;}

static inline uint32_t integertypes__u32pow2(uint32_t x){return (uint32_t)1<<x;}

static inline uint64_t integertypes__u64pow2(uint64_t x){return (uint64_t)1<<x;}

static inline uint8_t integertypes__u8lshift(uint8_t x, uint8_t n){return (uint8_t)x<<n;}

static inline uint16_t integertypes__u16lshift(uint16_t x, uint16_t n){return (uint16_t)x<<n;}

static inline uint32_t integertypes__u32lshift(uint32_t x, uint32_t n){return (uint32_t)x<<n;}

static inline uint64_t integertypes__u64lshift(uint64_t x, uint64_t n){return (uint64_t)x<<n;}

static inline uint8_t integertypes__u8rshift(uint8_t x, uint8_t n){return (uint8_t)x>>n;}

static inline uint16_t integertypes__u16rshift(uint16_t x, uint16_t n){return (uint16_t)x>>n;}

static inline uint32_t integertypes__u32rshift(uint32_t x, uint32_t n){return (uint32_t)x>>n;}

static inline uint64_t integertypes__u64rshift(uint64_t x, uint64_t n){return (uint64_t)x>>n;}

static inline uint8_t integertypes__u8times(uint8_t x, uint8_t y){return (uint8_t)(x * y);}

static inline uint16_t integertypes__u16times(uint16_t x, uint16_t y){return (uint16_t)(x * y);}

static inline uint32_t integertypes__u32times(uint32_t x, uint32_t y){return (uint32_t)(x * y);}

static inline uint64_t integertypes__u64times(uint64_t x, uint64_t y){return (uint64_t)(x * y);}

static inline uint8_t integertypes__u8div(uint8_t x, uint8_t y){return (uint8_t)(x/y);}

static inline uint16_t integertypes__u16div(uint16_t x, uint16_t y){return (uint16_t)(x/y);}

extern uint32_t integertypes__u32div(uint32_t ivar_2, uint32_t ivar_3);

static inline uint64_t integertypes__u64div(uint64_t x, uint64_t y){return (uint64_t)(x/y);}

static inline uint8_t integertypes__u8rem(uint8_t x, uint8_t y){return (uint8_t)(x%y);}

static inline uint16_t integertypes__u16rem(uint16_t x, uint16_t y){return (uint16_t)(x%y);}

static inline uint32_t integertypes__u32rem(uint32_t x, uint32_t y){return (uint32_t)(x%y);}

static inline uint64_t integertypes__u64rem(uint64_t x, uint64_t y){return (uint64_t)(x%y);}

static inline uint8_t integertypes__u8max(uint8_t x, uint8_t y){return (uint8_t)(x< y ? y : x);}

static inline uint16_t integertypes__u16max(uint16_t x, uint16_t y){return (uint16_t)(x< y ? y : x);}

static inline uint32_t integertypes__u32max(uint32_t x, uint32_t y){return (uint32_t)(x< y ? y : x);}

static inline uint64_t integertypes__u64max(uint64_t x, uint64_t y){return (uint64_t)(x< y ? y : x);}

static inline int8_t integertypes__i8max(int8_t x, int8_t y){return (int8_t)(x< y ? y : x);}

static inline int16_t integertypes__i16max(int16_t x, int16_t y){return (int16_t)(x< y ? y : x);}

static inline int32_t integertypes__i32max(int32_t x, int32_t y){return (int32_t)(x< y ? y : x);}

static inline int64_t integertypes__i64max(int64_t x, int64_t y){return (int64_t)(x< y ? y : x);}

static inline uint8_t integertypes__u8min(uint8_t x, uint8_t y){return (uint8_t)(x< y ? y : x);}

static inline uint16_t integertypes__u16min(uint16_t x, uint16_t y){return (uint16_t)(x< y ? y : x);}

static inline uint32_t integertypes__u32min(uint32_t x, uint32_t y){return (uint32_t)(x< y ? x : y);}

static inline uint64_t integertypes__u64min(uint64_t x, uint64_t y){return (uint64_t)(x< y ? x : y);}

static inline int8_t integertypes__i8min(int8_t x, int8_t y){return (int8_t)(x< y ? x : y);}

static inline int16_t integertypes__i16min(int16_t x, int16_t y){return (int16_t)(x< y ? x : y);}

static inline int32_t integertypes__i32min(int32_t x, int32_t y){return (int32_t)(x< y ? x : y);}

static inline int64_t integertypes__i64min(int64_t x, int64_t y){return (int64_t)(x< y ? x : y);}

static inline uint8_t integertypes__u8ceiling(mpq_t x){return (uint8_t)pvsceiling_q_u64(x);}

static inline uint16_t integertypes__u16ceiling(mpq_t x){return (uint16_t)pvsceiling_q_u64(x);}

static inline uint32_t integertypes__u32ceiling(mpq_t x){return (uint32_t)pvsceiling_q_u64(x);}

static inline uint64_t integertypes__u64ceiling(mpq_t x){return (uint64_t)pvsceiling_q_u64(x);}

static inline uint8_t integertypes__u8floor(mpq_t x){return (uint8_t)pvsfloor_q_u64(x);}

static inline uint16_t integertypes__u16floor(mpq_t x){return (uint16_t)pvsfloor_q_u64(x);}

static inline uint32_t integertypes__u32floor(mpq_t x){return (uint32_t)pvsfloor_q_u64(x);}

static inline uint64_t integertypes__u64floor(mpq_t x){return (uint64_t)pvsfloor_q_u64(x);}

static inline int8_t integertypes__i8ceiling(mpq_t x){return (int8_t)pvsceiling_q_i64(x);}

static inline int16_t integertypes__i16ceiling(mpq_t x){return (int16_t)pvsceiling_q_i64(x);}

static inline int32_t integertypes__i32ceiling(mpq_t x){return (int32_t)pvsceiling_q_i64(x);}

static inline int64_t integertypes__i64ceiling(mpq_t x){return (int64_t)pvsceiling_q_i64(x);}

static inline int8_t integertypes__i8floor(mpq_t x){return (int8_t)pvsfloor_q_i64(x);}

static inline int16_t integertypes__i16floor(mpq_t x){return (int16_t)pvsfloor_q_i64(x);}

static inline int32_t integertypes__i32floor(mpq_t x){return (int32_t)pvsfloor_q_i64(x);}

static inline int64_t integertypes__i64floor(mpq_t x){return (int64_t)pvsfloor_q_i64(x);}
#endif