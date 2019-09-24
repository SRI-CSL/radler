#include RADL_HEADER
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/bool.hpp"

class Kill {
  public:
    Kill();
    void step(const radl_in_t*, const radl_in_flags_t*, radl_out_t*, radl_out_flags_t*);
  private:
		rclcpp::Node::SharedPtr h;
		rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr pub;
}; 
