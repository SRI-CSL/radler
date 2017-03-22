
#include RADL_HEADER

#include "stdio.h"

typedef struct {
  int8_t cpt[40];
  int count;
} RADL_STATE;

void RADL_INIT_FUN(RADL_STATE* s) {
  int j;
  for (j=0; j<40; j++) {
    s->cpt[j] = 0;
  }
  s->count=0;

  FILE *fp;
  fp = fopen("source_printmessage", "w");
  if (fp == NULL) { 
    printf("Source: could not open file for writing.\n");
    return; 
  }
  fprintf(fp,"Source: file initialized\n"); 
  fclose (fp);

  printf("Source initialized, count= %d\n", s->count);
  return;
}

void RADL_STEP_FUN(RADL_STATE* s, const radl_in_t* i, const radl_in_flags_t* inf,
		radl_out_t* o, radl_out_flags_t* of) {
    // Get actual values from the can bus
  //o->o1->source_data = s->cpt;
  int j;
  for (j = 0; j < 40; j++) {
    o->o1->source_data[j] = s->cpt[j];
    s->cpt[j] = s->cpt[j] + 1;
  }
  printf("Item %d sent: %d\n", s->count, o->o1->source_data[0]);
  s->count++;
  return;
}

void RADL_FINISH_FUN(RADL_STATE* s) {
  printf("Source terminated. Final count=%d\n", s->count);
  return;
}
