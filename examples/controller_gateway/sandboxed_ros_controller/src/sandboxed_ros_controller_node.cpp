
/*
 * Sandboxed usual ROS controller node stub
 */

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"
#include "std_msgs/msg/float32.hpp"

#include <iostream>

void input_handler(const std_msgs::msg::Int32::ConstSharedPtr msg) {
  std::cout << "sanbox input: " << msg->data << std::endl;
}

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("sandboxed_controller");
  auto sub = node->create_subscription<std_msgs::msg::Int32>("sandbox_input1", input_handler, rmw_qos_profile_default);
  auto pub = node->create_publisher<std_msgs::msg::Float32>("sandbox_output1", rmw_qos_profile_default);
  rclcpp::Rate loop_rate(1);
  float output = 0.1;
  while (rclcpp::ok()) {
    rclcpp::spin_some(node);
    std_msgs::msg::Float32 o;
    o.data = output;
    pub->publish(o);
    std::cout << "sanbox output: " << o.data << std::endl;
    output *= 3;
    loop_rate.sleep();
  }
  return 0;
}
