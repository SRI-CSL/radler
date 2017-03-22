/*
 * This file defines generic identity node classes.
 * 
 * The <y>th input (resp. output) has to be named i<y> (resp. o<y>).
 *
 * Note that being the identity, it forwards the flags instead of blending them.
 *
 */

#include RADL_HEADER


class identity_1 {
	public:
	void step(const radl_in_t * i, const radl_in_flags_t *inf,
		  radl_out_t * o, radl_out_flags_t * of) {
		*o->o1 = *i->i1;
		of->o1 =inf->i1;
	}
};

