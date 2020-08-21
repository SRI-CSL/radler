#include RADL_HEADER

#include "ros/ros.h"

#include <sensor_msgs/BatteryState.h>
#include <mavros_msgs/SetMode.h>

class Gateway 
{
public:
 	Gateway();
 	void step(const radl_in_t* i, const radl_in_flags_t* i_f, radl_out_t* o, radl_out_flags_t* o_f);
private:
 	ros::NodeHandle nh;
	ros::ServiceClient client; 
 	ros::Subscriber sub;
 	sensor_msgs::BatteryState::ConstPtr out_mbox;
	void battery_state_cb(const sensor_msgs::BatteryState::ConstPtr& bs);
};

