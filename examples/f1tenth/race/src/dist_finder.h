#include RADL_HEADER
#include "ros/ros.h"

class DistFinder {
  public:
    DistFinder();
    void step(const radl_in_t*, const radl_in_flags_t*, radl_out_t*, radl_out_flags_t*);
  private:
    ros::NodeHandle h;
    ros::Subscriber sub;
}; 
