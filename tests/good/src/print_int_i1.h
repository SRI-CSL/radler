
#include RADL_HEADER

#include "stdio.h"

typedef struct {uint8_t filler;} RADL_STATE;

void RADL_INIT_FUN(RADL_STATE* s) {}

void RADL_STEP_FUN(RADL_STATE* s, const radl_in_t * i, const radl_in_flags_t *inf,
		  radl_out_t * o, radl_out_flags_t * of) {
	printf("Received: %d\n", i->i1->data);
}

void RADL_FINISH_FUN(RADL_STATE* s) {}
