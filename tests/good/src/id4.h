/*
 * This file defines generic identity node classes.
 * 
 * The <y>th input (resp. output) has to be named i<y> (resp. o<y>).
 *
 * Note that being the identity, it forwards the flags instead of blending them.
 *
 */

#include RADL_HEADER

class identity_4 {
	public:
	void step(const radl_in_t * i, const radl_in_flags_t *inf,
		  radl_out_t * o, radl_out_flags_t * of) {
		*o->o1 = *i->i1;
		*o->o2 = *i->i2;
		*o->o3 = *i->i3;
		*o->o4 = *i->i4;
		of->o1 =inf->i1;
		of->o2 =inf->i2;
		of->o3 =inf->i3;
		of->o4 =inf->i4;
	}
};

