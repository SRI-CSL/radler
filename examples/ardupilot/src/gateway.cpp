#include "gateway.h"

#include <iostream>

#include "sensor_msgs/msg/battery_state.hpp"
#include "mavros_msgs/srv/set_mode.hpp"
#include "nav_msgs/msg/odometry.hpp"
#include "std_msgs/msg/float64.hpp"

using namespace std;

Gateway::Gateway() 
{
  node = rclcpp::Node::make_shared("gateway");

  rtl_client = node->create_client<mavros_msgs::srv::SetMode>("/mavros/set_mode");
  bat_sub = node->create_subscription<sensor_msgs::msg::BatteryState>("/mavros/battery", rclcpp::SensorDataQoS(), std::bind(&Gateway::battery_state_cb, this, std::placeholders::_1));
  pos_sub = node->create_subscription<nav_msgs::msg::Odometry>("/mavros/global_position/local", rclcpp::SensorDataQoS(), std::bind(&Gateway::position_cb, this, std::placeholders::_1));
  alt_sub = node->create_subscription<std_msgs::msg::Float64>("/mavros/global_position/rel_alt", rclcpp::SensorDataQoS(), std::bind(&Gateway::altitude_cb, this, std::placeholders::_1));
}

void Gateway::step(const radl_in_t* i, const radl_in_flags_t* i_f, radl_out_t* o, radl_out_flags_t* o_f) 
{
  auto request = std::make_shared<mavros_msgs::srv::SetMode::Request>();
  request->base_mode = 0;

  rclcpp::spin_some(node);
  if (this->bat_out_mbox) {
    o->battery_status->percentage = bat_out_mbox->percentage;
    cout << "gateway battery : " << o->battery_status->percentage  << endl;
    radl_turn_off(radl_STALE, &o_f->battery_status);
  } else {
    radl_turn_on(radl_STALE, &o_f->battery_status);
  }
  radl_turn_off(radl_TIMEOUT, &o_f->battery_status);

  if (!radl_is_stale(i_f->mode_change_rtl) && !radl_is_timeout(i_f->mode_change_rtl)) {
    if (i->mode_change_rtl->val) { 
      cout << "mode change to RTL" << endl;
      request->custom_mode = "RTL";

      while (!rtl_client->wait_for_service(1s)) {
        if (!rclcpp::ok()) {
          cout <<  "interrupted while waiting for the service" << endl;
          return;
        }
        cout << "service not available, waiting again" << endl;
      }
      auto result = rtl_client->async_send_request(request);
      if (rclcpp::spin_until_future_complete(node, result) != rclcpp::FutureReturnCode::SUCCESS)
        cout << "failed to call service rtl" << endl;
    }
  }
  if (this->pos_out_mbox) {
    o->position->x = this->pos_out_mbox->pose.pose.position.x;
    o->position->y = this->pos_out_mbox->pose.pose.position.y;
    cout << "gateway pos : " << o->position->x << " " << o->position->y << endl;
    radl_turn_off(radl_STALE, &o_f->position);
  } else {
    radl_turn_on(radl_STALE, &o_f->position);
  }
  radl_turn_off(radl_TIMEOUT, &o_f->position);

  if (this->alt_out_mbox) {
    o->altitude->data = this->alt_out_mbox->data;
    cout << "gateway altitude : " << o->altitude->data << endl;
    radl_turn_off(radl_STALE, &o_f->altitude);
  } else {
    radl_turn_on(radl_STALE, &o_f->altitude);
  }
  radl_turn_off(radl_TIMEOUT, &o_f->altitude);
}

void Gateway::battery_state_cb(const sensor_msgs::msg::BatteryState::ConstSharedPtr bs) 
{
  this->bat_out_mbox = bs;
}

void Gateway::position_cb(const nav_msgs::msg::Odometry::ConstSharedPtr pos)
{
  this->pos_out_mbox = pos;
}

void Gateway::altitude_cb(const std_msgs::msg::Float64::ConstSharedPtr alt)
{
  this->alt_out_mbox = alt;
}
