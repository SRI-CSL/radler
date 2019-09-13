#include RADL_HEADER
#include "ros/ros.h"

class Kill {
  public:
    Kill();
    void step(const radl_in_t*, const radl_in_flags_t*, radl_out_t*, radl_out_flags_t*);
  private:
    ros::NodeHandle h;
    ros::Publisher pub;
}; 
