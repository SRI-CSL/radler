/*
 * This file defines a RADL <-> ROS gateway node class
 */

#include RADL_HEADER

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"
#include "std_msgs/msg/float32.hpp"

#include <iostream>

std_msgs::msg::Float32::SharedPtr out_mbox;

class Gateway {
private:
  rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr pub;
  rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr sub;
  rclcpp::Node::SharedPtr h;
public:
  Gateway() {
    //Uncomment if the gateway is used when radl doesn't use ROS backend.
    h = rclcpp::Node::make_shared("controller_gateway");

    //Declared sandbox publications
    pub = h->create_publisher<std_msgs::msg::Int32>("sandbox_input1", rmw_qos_profile_default);

    //Declared sandbox subscriptions
    sub = h->create_subscription<std_msgs::msg::Float32>("sandbox_output1", subhandler, rmw_qos_profile_default);
  }

  static void subhandler(const std_msgs::msg::Float32::SharedPtr msg) {
    std::cout << "sub: " << msg->data << std::endl;
    out_mbox = msg;
  }

  void step(const radl_in_t* i, const radl_in_flags_t* i_f, radl_out_t* o, radl_out_flags_t* o_f) {
    //Forward inputs to sandbox
    auto out_msg = std::make_shared<std_msgs::msg::Int32>();
    out_msg->data = i->input1->data;
    this->pub->publish(out_msg);
    std::cout << "pub: " << out_msg->data << std::endl;

    //Forward sandbox to outputs
    rclcpp::spin_some(this->h);
    if (out_mbox) {
      o->output1->data = out_mbox->data;
    } else {
      radl_turn_on(radl_STALE, &o_f->output1);
    }
  }
};
