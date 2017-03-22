
#include RADL_HEADER

class Pub {
	unsigned int cpt;
	public:
	Pub() : cpt(0) {}
	void step(const radl_in_t *i, const radl_in_flags_t *inf,
			radl_out_t *o, radl_out_flags_t *of) {
		o->o1->x = cpt++;
	}
};

