/*
 * This file defines a RADL <-> ROS gateway node class
 */

#include RADL_HEADER

#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include "std_msgs/Float32.h"

class Gateway {
public:
  Gateway() {
    //Uncomment if the gateway is used when radl doesn't use ROS backend.
    //ros::init(n, NULL, "estop_gateway");

    //Declared sandbox publications
    pub = h.advertise<std_msgs::Int32>("sandbox_input1", 2);

    // Declared sandbox subscriptions
    sub = h.subscribe("sandbox_output1", 2, &Gateway::subhandler, this);
  }

  void subhandler(const std_msgs::Float32::ConstPtr& msg) {
    this->out_mbox = msg;
  }

  void step(const radl_in_t* i, const radl_in_flags_t* i_f,
            radl_out_t* o, radl_out_flags_t* o_f) {
    //Forward inputs to sandbox
    std_msgs::Int32 out_msg;
    out_msg.data = i->input1->data;
    this->pub.publish(out_msg);

    //Forward sandbox to outputs
    if (this->out_mbox) {
      o->output1->data = this->out_mbox->data;
    } else {
      radl_turn_on(radl_STALE, &o_f->output1);
    }
  }

private:
  ros::NodeHandle h;
  ros::Publisher pub;
  ros::Subscriber sub;
  std_msgs::Float32::ConstPtr out_mbox;
};

