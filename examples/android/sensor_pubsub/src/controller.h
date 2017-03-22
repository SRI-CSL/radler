#include RADL_HEADER

class Controller {
        private:
                ros::NodeHandle nh;
                ros::Publisher speaker_pub;
 	public:
		Controller();
  		void step(const radl_in_t*, const radl_in_flags_t*, radl_out_t*, radl_out_flags_t*);
};
