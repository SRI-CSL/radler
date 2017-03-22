
#include RADL_HEADER


typedef struct {
	uint32_t cpt;
} RADL_STATE;

void RADL_INIT_FUN(RADL_STATE* s) {
	s->cpt = 42;
}

void RADL_STEP_FUN(RADL_STATE* s, const radl_in_t* i, const radl_in_flags_t* inf,
		radl_out_t* o, radl_out_flags_t* of) {
    // Get actual values from the can bus
	o->o1->data = s->cpt++;
}

void RADL_FINISH_FUN(RADL_STATE* s) {}
