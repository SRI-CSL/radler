#include RADL_HEADER

class Compass {
        private:
                ros::NodeHandle nh;
                ros::Subscriber compass_sub;
 	public:
		Compass();
  		void step(const radl_in_t*, const radl_in_flags_t*, radl_out_t*, radl_out_flags_t*);
};
