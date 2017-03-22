/*
 * Created on May, 2014
 * @author: Léonard Gérard leonard.gerard@sri.com
 *
 *
 * Flags handling
 *
 * Use an uint instead of a bitfield to be compatible.
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef uint8_t radl_flags_t;

#define radl_i2f(X) ((radl_flags_t)X)

/***
 * Failure flags are expected to be raised even in sane systems.
 *
 *   The stale_mbox flag indicate that the value in the mailbox is the same
 * as the one provided last time to the step function because no knew value
 * has been received since then. This is for example expected with a publisher
 * whose period is bigger than the one of its subscriber.
 *   The stale_value flag indicate that the value received was marked by the
 * publisher has stale.
 */
#define radl_OPERATIONAL_FLAGS      radl_i2f(15)

#define radl_STALE_VALUE            radl_i2f(1)
#define radl_STALE_MBOX             radl_i2f(2)
#define radl_STALE                  radl_i2f(3)

#define radl_OPERATIONAL_1          radl_i2f(4)
#define radl_OPERATIONAL_2          radl_i2f(8)

/***
 * Failure flags indicate that the system isn't operational.
 *
 *   The timeout_mbox flag indicate that the receiver mailbox should
 * have received a message recently but hasn't.
 * The "recently" is computed knowing the channel maximum latency
 * and the period of the publisher and subscriber)
 *   The timeout_value flag indicate that the value received was marked by
 * the publisher has timeout.
 */
#define radl_FAILURE_FLAGS        ~radl_OPERATIONAL_FLAGS

#define radl_TIMEOUT_VALUE        radl_i2f(16)
#define radl_TIMEOUT_MBOX         radl_i2f(32)
#define radl_TIMEOUT              radl_i2f(48)

#define radl_FAILURE_1            radl_i2f(64)
#define radl_FAILURE_2            radl_i2f(128)


#define radl_MBOX_FLAGS           (radl_STALE_MBOX | radl_TIMEOUT_MBOX)
#define radl_VALUE_FLAGS          (radl_STALE_VALUE | radl_TIMEOUT_VALUE)

/***
 * Handy user functions to manipulate RADL flags.
 */

/* radl_is_stale(f) returns if the (compound) stale flag of f is on. */
static inline
int radl_is_stale(radl_flags_t f) { return !!(f & radl_STALE); };

static inline
int radl_is_value_stale(radl_flags_t f) { return !!(f & radl_STALE_VALUE); };
static inline
int radl_is_mbox_stale(radl_flags_t f) { return !!(f & radl_STALE_MBOX); };


/* radl_is_failing(f) returns true if any failure flag of f is on. */
static inline
int radl_is_failing(radl_flags_t f) { return !!(f & radl_FAILURE_FLAGS); };


/* radl_is_stale(f) returns if the (compound) timeout flag of f is on. */
static inline
int radl_is_timeout(radl_flags_t f) { return !!(f & radl_TIMEOUT); };

static inline
int radl_is_value_timeout(radl_flags_t f) { return !!(f & radl_TIMEOUT_VALUE); };
static inline
int radl_is_mbox_timeout(radl_flags_t f) { return !!(f & radl_TIMEOUT_MBOX); };


/* radl_turn_on(radl_STALE, &f) turn on the stale flag of f. */
static inline
void radl_turn_on(radl_flags_t f, radl_flags_t * x) { *x |= f; };

/* radl_turn_off(radl_STALE, &f) turn off the stale flag of f. */
static inline
void radl_turn_off(radl_flags_t f, radl_flags_t * x) { *x &= ~f; };

static inline
radl_flags_t radl_mbox_flags_to_value(radl_flags_t f) {
  return (f | ((f>>1) & (radl_VALUE_FLAGS))) & ~radl_MBOX_FLAGS;
}

#ifdef __cplusplus
}
#endif
