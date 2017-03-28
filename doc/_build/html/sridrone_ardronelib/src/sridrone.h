#include RADL_HEADER
//#include <ardrone/ardrone.h>

class SRIDrone {
//	private:
//    		ARDrone ardrone;
 	public:
  		SRIDrone();
  		void step(const radl_in_t*, const radl_in_flags_t*, radl_out_t*, radl_out_flags_t*);
};
