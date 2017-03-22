/*
 * Created on Sept, 2014
 * @author: Léonard Gérard leonard.gerard@sri.com
 *
 * Minimal time implementation.
 *
 * Duration are in nanoseconds, stored as a signed 2^64 integer.
 * The time is described as a duration from epoch, meaning that it will
 * overflow during the year 2262 ((2^63-1)/(10^9)/86400/365 years after epoch).
 *
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <time.h>
#include <assert.h>

#define pow10_9 1000000000

typedef int64_t radl_duration_t;


/*
 * Print format to allow printing of the raw date value.
 *
 * Example usage:
 * printf("The current date %" RADL_PRItime " in nanoseconds!", radl_gettime());
 *
 * Note the % which is necessary (usual C way of printing types see inttypes.h)
 *
 */
// Get the print format of int64_t
#include <inttypes.h>
#define RADL_PRItime PRId64



static inline
radl_duration_t radl_timesub(radl_duration_t t1, radl_duration_t t2) {
	return t2-t1;
}
static inline
radl_duration_t radl_timeadd(radl_duration_t t1, radl_duration_t t2) {
	return t1+t2;
}

static inline
radl_duration_t radl_from_secnsec(int64_t sec, int64_t nsec) {
	/* It is safe to give unsigned values to this function and let
	 * the implicit C casting take place (unless they are too big!)
	 */
	return sec*pow10_9+nsec;
}

static inline
void radl_to_secnsec(radl_duration_t t, int64_t* sec, uint32_t* nsec) {
	*sec = t/pow10_9;
	*nsec = t - (*sec) * pow10_9;
}

static inline
void radl_to_timespec(radl_duration_t time, struct timespec* t) {
	assert(time>0);
	int64_t s;
	uint32_t ns;
	radl_to_secnsec(time, &s, &ns);
	t->tv_sec = s;
	t->tv_nsec = ns;
}

static inline
radl_duration_t radl_from_timespec(struct timespec t) {
  return radl_from_secnsec(t.tv_sec, t.tv_nsec);
}

static inline
time_t radl_to_time_t(radl_duration_t time) {
	assert(time>0);
	return (time_t) (time/pow10_9);
}

static inline
radl_duration_t radl_from_time_t(time_t time) {
  return time*pow10_9;
}


static inline
int64_t radl_to_nsec(radl_duration_t t) { return t; }


radl_duration_t radl_gettime();


struct radl_timer_state {
  radl_duration_t period;
  radl_duration_t last_time;
};

void radl_timer_init(struct radl_timer_state *, radl_duration_t);
int radl_timer_wait(struct radl_timer_state *);


#ifdef __cplusplus
}
#endif
