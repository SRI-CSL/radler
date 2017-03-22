
#include <stdio.h>
#include <unistd.h>
#include "radl_lib.h"

#include <time.h>

int main(){
  radl_init_lib();
  int i;
  printf("The time will be displayed four times below.\n"
         "It reads in nanoseconds since epoch.\n"
         "It should be to around %lu sec\n",
         time(NULL));
  for (i=0; i<4; i++){
    printf("%lld\n", radl_gettime()/1000000000);
    sleep(1);
  }
  printf("The minimal difference between two call to radl_getdate\n"
         "should be around 100 nanoseconds:\n");
  radl_duration_t t1, t2;
  for (i=0; i<4; i++){
    t1 = radl_gettime();
    t2 = radl_gettime();
    printf("%lld\n", t2-t1);
    sleep(1);
  }
  return 0;
}
