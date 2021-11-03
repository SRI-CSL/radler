#include RADL_HEADER

#include "rclcpp/rclcpp.hpp"
#include "rclcpp/qos.hpp"

#include "sensor_msgs/msg/battery_state.hpp"
#include "mavros_msgs/srv/command_tol.hpp"

class Gateway 
{
public:
 	Gateway();
 	void step(const radl_in_t* i, const radl_in_flags_t* i_f, radl_out_t* o, radl_out_flags_t* o_f);
private:
	std::shared_ptr<rclcpp::Node> node;

	rclcpp::Client<mavros_msgs::srv::CommandTOL>::SharedPtr land_client;

	rclcpp::Subscription<sensor_msgs::msg::BatteryState>::SharedPtr bat_sub;
 	sensor_msgs::msg::BatteryState::ConstSharedPtr bat_out_mbox;
	void battery_state_cb(const sensor_msgs::msg::BatteryState::ConstSharedPtr bs);
};
