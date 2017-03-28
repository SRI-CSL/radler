#include RADL_HEADER

class SRIDrone {
	private:
  		ros::NodeHandle nh;
		ros::Subscriber navdata_sub;
 	public:
  		SRIDrone();
  		void step(const radl_in_t*, const radl_in_flags_t*, radl_out_t*, radl_out_flags_t*);
};
