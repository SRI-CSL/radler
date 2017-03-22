
/*
 * Sandboxed usual ROS controller node stub
 */

#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include "std_msgs/Float32.h"

#include <iostream>

void input_handler(const std_msgs::Int32::ConstPtr& msg) {
  std::cout << "sanbox input: " << msg->data << std::endl;
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "sandboxed_controller");
  ros::NodeHandle h;
  ros::Subscriber sub = h.subscribe<std_msgs::Int32>("sandbox_input1", 2, input_handler);
  ros::Publisher pub = h.advertise<std_msgs::Float32>("sandbox_output1", 2);
  ros::Rate loop_rate(1);
  float output = 0.1;
  while (ros::ok()) {
    ros::spinOnce();
    std_msgs::Float32 o;
    o.data = output;
    pub.publish(o);
    std::cout << "sanbox output: " << o.data << std::endl;
    output *= 3;
    loop_rate.sleep();
  }
  return 0;
}
