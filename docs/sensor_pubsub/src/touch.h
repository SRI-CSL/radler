#include RADL_HEADER

class Touch {
        private:
                ros::NodeHandle nh;
                ros::Subscriber touch_sub;
 	public:
		Touch();
  		void step(const radl_in_t*, const radl_in_flags_t*, radl_out_t*, radl_out_flags_t*);
};
