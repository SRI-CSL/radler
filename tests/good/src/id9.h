/*
 * This file defines generic identity node classes.
 * 
 * The <y>th input (resp. output) has to be named i<y> (resp. o<y>).
 *
 * Note that being the identity, it forwards the flags instead of blending them.
 *
 */

#include RADL_HEADER

class identity_9 {
	public:
	void step(const radl_in_t * i, const radl_in_flags_t *inf,
		  radl_out_t * o, radl_out_flags_t * of) {
		*o->o1 = *i->i1;
		*o->o2 = *i->i2;
		*o->o3 = *i->i3;
		*o->o4 = *i->i4;
		*o->o5 = *i->i5;
		*o->o6 = *i->i6;
		*o->o7 = *i->i7;
		*o->o8 = *i->i8;
		*o->o9 = *i->i9;
		of->o1 =inf->i1;
		of->o2 =inf->i2;
		of->o3 =inf->i3;
		of->o4 =inf->i4;
		of->o5 =inf->i5;
		of->o6 =inf->i6;
		of->o7 =inf->i7;
		of->o8 =inf->i8;
		of->o9 =inf->i9;
	}
};
