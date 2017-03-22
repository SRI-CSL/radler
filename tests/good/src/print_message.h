
#include RADL_HEADER

#include "stdio.h"

typedef struct {int count;} RADL_STATE;

void RADL_INIT_FUN(RADL_STATE* s) {
  s->count=0;

  FILE *fp;
  fp = fopen("sink_printmessage", "w");
  if (fp == NULL) { 
    printf("Sink: could not open file for writing.\n");
    return; 
  }
  fprintf(fp,"Sink: file initialized\n"); 
  fclose (fp);

  printf("Sink initialized, count= %d\n", s->count);
  return;
}

void RADL_STEP_FUN(RADL_STATE* s, const radl_in_t * i, const radl_in_flags_t *inf,
		  radl_out_t * o, radl_out_flags_t * of) {
        
  printf("Item %d received: %d\n", s->count, i->i1->sink_data[0]);
  s->count++;
  return;
}

void RADL_FINISH_FUN(RADL_STATE* s) {
  printf("Sink terminated. Final count=%d\n", s->count);
  return;
}
