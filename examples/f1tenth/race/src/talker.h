#include RADL_HEADER 
#include "rclcpp/rclcpp.hpp"
#include "race/msg/drive_values.hpp" 

class Talker {
  public:
    Talker();
    void step(const radl_in_t * in, const radl_in_flags_t* inflags, radl_out_t * out, radl_out_flags_t* outflags);
  private:
		rclcpp::Node::SharedPtr h;
		rclcpp::Publisher<race::msg::DriveValues>::SharedPtr pub;
};
