#include RADL_HEADER 
#include "ros/ros.h"

class Talker {
  public:
    Talker();
    void step(const radl_in_t * in, const radl_in_flags_t* inflags, radl_out_t * out, radl_out_flags_t* outflags);
  private:
    ros::NodeHandle h;
    ros::Publisher pub;
};
