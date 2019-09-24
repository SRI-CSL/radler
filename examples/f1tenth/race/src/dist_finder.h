#include RADL_HEADER
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"

class DistFinder {
  public:
    DistFinder();
    void step(const radl_in_t*, const radl_in_flags_t*, radl_out_t*, radl_out_flags_t*);
  private:
		rclcpp::Node::SharedPtr h;
		rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr sub;
}; 
