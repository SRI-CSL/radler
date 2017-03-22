/*
 * Created on Feb, 2015
 * @author: Léonard Gérard leonard.gerard@sri.com
 *
 * Single entry point to RADL libraries
 * This file contains internal helpers, the user header is radl_lib.h
 */


#pragma once

#include "radl_time.h"
#include "radl_flags.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <unistd.h>         /* posix macros */
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <sys/time.h>       /* gettimeofday */
#include <stdint.h>
#include <stdio.h>

#ifdef __MACH__
#include <mach/mach_time.h> /* mach_absolute_time */
#include <mach/mach.h>      /* host_get_clock_service, mach_... */
#endif

#define PPCAT_NX(A, B) A ## B
#define PPCAT(A, B) PPCAT_NX(A,B)
#define STRINGIZE_NX(X) #X
#define STRINGIZE(X) STRINGIZE_NX(X)


/*
 * Static assertion macro
 * http://www.pixelbeat.org/programming/gcc/static_assert.html
 */
#define ASSERT_CONCAT_(a, b) a##b
#define ASSERT_CONCAT(a, b) ASSERT_CONCAT_(a, b)
/* These can't be used after statements in c89. */
#ifdef __COUNTER__
  #define STATIC_ASSERT(e,m) \
    ;enum { ASSERT_CONCAT(static_assert_, __COUNTER__) = 1/(!!(e)) }
#else
  /* This can't be used twice on the same line so ensure if using in headers
   * that the headers are not included twice (by wrapping in #ifndef...#endif)
   * Note it doesn't cause an issue when used on same line of separate modules
   * compiled with gcc -combine -fwhole-program.  */
  #define STATIC_ASSERT(e,m) \
    ;enum { ASSERT_CONCAT(assert_line_, __LINE__) = 1/(!!(e)) }
#endif


/*
 * We need to check float and double sizes to ensure all platforms agree
 */

STATIC_ASSERT(sizeof(float)==4,"If error here, float needs to be of size 4.");
STATIC_ASSERT(sizeof(double)==8,"If error here, double needs to be of size 8.");



/*
 * Module initialization function
 */
void radl_init_lib();




/* This function main purpose is to help compute the mailboxes timeout
 * flag. The idea is to count the number of consecutive steps where the mbox
 * is stale. This count should never be more than the value we return.
 * If the publisher WCET is given, the computed value may be more precise,
 * otherwise, we assume the WCET is the period.
 */

/*
#include <math.h>

int max_stale_steps(int pub_period, int maxlatency, int sub_period, int pub_each, int pub_wcet) {
  if (pub_wcet <= 0) {
    pub_wcet = pub_period;
  }
  return ceil((pub_period * pub_each + pub_wcet + maxlatency) / sub_period);
}
*/

/*
 * This macro is used to make sure that handling of flags is coherent
 * among the different backends.
 *
 * It's purpose is to gather flags to compute the default output flag set
 * and compute the flags of the input input_name.
 *
 * flags: the flags coming with the input value, we need to clean them by
 *     keeping only the value flags (users may write mbox flags in outputs).
 * is_stale: whether the mailbox was stale.
 * stale_counter: a counter managed by this macro to compute timeout.
 * stale_max: the number of consecutive stale times before going in timeout.
 *
 */
#define RADL__MNG_FLAGS(input_name, flags, is_stale, stale_counter, stale_max)\
    _in_flags.input_name = radl_mbox_flags_to_value(flags);                   \
    if (is_stale) {                                                           \
      radl_turn_on(radl_STALE_MBOX, &_in_flags.input_name);                   \
      stale_counter++;                                                        \
      if (stale_counter >= stale_max) {                                       \
        radl_turn_on(radl_TIMEOUT_MBOX, &_in_flags.input_name);               \
      }                                                                       \
    } else {                                                                  \
      stale_counter = 0;                                                      \
    }                                                                         \
    _gathered_flags |= _in_flags.input_name;


#define RADL__PRINT_HELPER(fmt, ...)                                          \
    printf("[%s.%s] " fmt "\n%s", STRINGIZE(RADL_MODULE_NAME)                 \
                                , STRINGIZE(RADL_NODE_NAME)                   \
                                , __VA_ARGS__)

#define RADL__PRINTF(...)                                                     \
    printf(__VA_ARGS__)

//Include the user helpers by default
#include "radl_lib.h"

#ifdef __cplusplus
}
#endif
