
#include "radl__lib.h"
#include "src/radl.h"

void pervasives_init_hook(){
    *radln_4_radl.start_time = radl_gettime();
}
