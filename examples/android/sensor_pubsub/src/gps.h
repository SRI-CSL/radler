#include RADL_HEADER

class GPS {
        private:
                ros::NodeHandle nh;
                ros::Subscriber gps_sub;
 	public:
		GPS();
  		void step(const radl_in_t*, const radl_in_flags_t*, radl_out_t*, radl_out_flags_t*);
};
