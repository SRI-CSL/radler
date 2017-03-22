
#include RADL_HEADER

class Sub {
	public:
	void step(const radl_in_t *i, const radl_in_flags_t *inf,
			radl_out_t *o, radl_out_flags_t *of) {
		RADL_PRINT("stale: %d (mbox: %d) timeout: %d (mbox: %d) value: %d",
				radl_is_stale(inf->i1),
				radl_is_mbox_stale(inf->i1),
			        radl_is_timeout(inf->i1),
			        radl_is_mbox_timeout(inf->i1),
			        i->i1->x);
	}
};
