#include RADL_HEADER

#include "ros/ros.h"

#include <sensor_msgs/BatteryState.h>
#include <std_msgs/Float64.h>
#include <mavros_msgs/SetMode.h>
#include <geometry_msgs/PoseStamped.h>
#include <nav_msgs/Odometry.h>

class Gateway 
{
public:
 	Gateway();
 	void step(const radl_in_t* i, const radl_in_flags_t* i_f, radl_out_t* o, radl_out_flags_t* o_f);
private:
 	ros::NodeHandle nh;

	ros::ServiceClient mode_srv; 

 	ros::Subscriber bat_sub;
 	sensor_msgs::BatteryState::ConstPtr bat_out_mbox;
	void battery_state_cb(const sensor_msgs::BatteryState::ConstPtr& bs);

  ros::Subscriber pos_sub;
  nav_msgs::Odometry::ConstPtr pos_out_mbox;
  void position_cb(const nav_msgs::Odometry::ConstPtr& pos);

 	ros::Subscriber alt_sub;
 	std_msgs::Float64::ConstPtr alt_out_mbox;
	void altitude_cb(const std_msgs::Float64::ConstPtr& alt);

	ros::Publisher alt_pub;
};

