#include RADL_HEADER

#include "rclcpp/rclcpp.hpp"
#include "rclcpp/qos.hpp"

#include "ros_healthcare_msg/msg/hr.hpp"
#include "ros_healthcare_msg/msg/rr.hpp"
#include "sensor_msgs/msg/imu.hpp"
#include "ros_healthcare_msg/msg/ecg_leads.hpp"
#include "std_msgs/msg/float64.hpp"

class Gateway 
{
public:
  Gateway();
  void step(const radl_in_t* i, const radl_in_flags_t* i_f, radl_out_t* o, radl_out_flags_t* o_f);
private:
  std::shared_ptr<rclcpp::Node> node;
  rclcpp::Publisher<ros_healthcare_msg::msg::HR>::SharedPtr hr_pub;
  rclcpp::Publisher<ros_healthcare_msg::msg::RR>::SharedPtr rr_pub;
  rclcpp::Publisher<sensor_msgs::msg::Imu>::SharedPtr imu_pub;
  rclcpp::Publisher<ros_healthcare_msg::msg::ECGLeads>::SharedPtr ecg_pub;
};
