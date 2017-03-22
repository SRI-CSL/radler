/*
 * Created on Oct, 2014
 * @author: Léonard Gérard leonard.gerard@sri.com
 *
 * Single entry point to RADL libraries
 */

//TODO: 8 document which platforms are supported.
//TODO: 9 Handle real mach platforms and win32 platforms

#include "radl__lib.h"


#ifdef __certikos__
#include <syscall.h> // Used for sys_yield()
#else
#include <unistd.h>         // for posix macros
#include <errno.h>          // for perror
#include <stdlib.h>         // for timeval and gettimeofday
#endif

#include <stdio.h>

static radl_duration_t time_offset;


#if defined __MACH__
static mach_timebase_info_data_t timebase;
#endif


static inline radl_duration_t current_monotonic_time(){
  #ifdef __certikos__
  return monotonic_nanosec();

  #elif _POSIX_TIMERS>=0
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return radl_from_secnsec(t.tv_sec, t.tv_nsec);

  #elif defined __MACH__
    uint64_t t = mach_absolute_time();
    return t * (uint64_t)timebase.numer / (uint64_t)timebase.denom;

  #else // win32, etc.
    #error "radl_lib currently support only posix and mach and certikos."
  #endif
}


void radl_init_lib(){
  static int initialized = 0;
  if (!initialized){
    #if defined __MACH__
      if (mach_timebase_info(&timebase) != 0) abort();
    #endif

    //Compute time_offset
    struct timeval start;
    radl_duration_t start_time;
#ifdef __certikos__
    gettimeofday(&start);
#else
    gettimeofday(&start, NULL);
#endif
    start_time = radl_from_secnsec(start.tv_sec, start.tv_usec * 1000);
    time_offset = start_time - current_monotonic_time();
  }
  initialized = 1;
}


radl_duration_t radl_gettime(){
  /* Return the duration since epoch, while ensuring monotony during a boot
   * It is not ensured (and usually won't be) the same across machines.
   */
  return current_monotonic_time() + time_offset;
}



void radl_timer_init(struct radl_timer_state* s, radl_duration_t period) {
  s->period = period;
  s->last_time = current_monotonic_time();
}

/*
 * Precision of sleep  is expected to be close to 0.1 usec,
 * -> this may return as early as 0.1usec ahead of expected period.
 *
 * There is currently no over bound on the period on supported platforms
 *   (none of them allow for realtime scheduling).
 *
 * Returns 0 if we are doing fine
 * -1 if we overshoot the period
 * -2 if sleeping failed
 */
int radl_timer_wait(struct radl_timer_state* s) {
  radl_duration_t next_time = s->last_time + s->period;
  s->last_time = next_time;

  radl_duration_t current = current_monotonic_time();

  if (current > next_time) { // We overshoot the deadline
    // Since the guarantees are already violated for this period,
    // let's be gentle for the next one and try to catch up
    s->last_time = current;
    return -1;
  }

#ifdef __certikos__
  // Do not try to sleep for less than 0.1usec
  while (current < (next_time - 100)) {
      /* Certikos yield may be dangerous since it binds our scheduling to their.
       * Moreover, it doesn't really help for cpu burn.
       * TODO: Do a cpu dependent low power waiting.
      */
//    sys_yield();

    current = current_monotonic_time();
  }

#else
  int r = 0;
  radl_duration_t sleep_time = next_time - current;
  struct timespec st;
  radl_to_timespec(sleep_time, &st);
  do {
    if (st.tv_sec <= 0 && st.tv_nsec < 100) {
      continue; // Do not try to sleep for less than 0.1usec
    }
    r = nanosleep(&st, &st);
  }
  while(r == -1 && errno == EINTR);
  if (r == -1) return -2;
#endif

  return 0;
}
