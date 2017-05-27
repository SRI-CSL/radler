#include RADL_HEADER
#include <image_transport/image_transport.h>

class SRIDrone {
	private:
  		ros::NodeHandle nh;
		ros::Subscriber navdata_sub;
		image_transport::Subscriber image_sub;
 	public:
  		SRIDrone();
  		void step(const radl_in_t*, const radl_in_flags_t*, radl_out_t*, radl_out_flags_t*);
};
