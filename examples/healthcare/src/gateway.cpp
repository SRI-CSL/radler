#include "gateway.h"

#include <iostream>

#include "ros_healthcare_msg/msg/hr.hpp"
#include "ros_healthcare_msg/msg/rr.hpp"
#include "sensor_msgs/msg/imu.hpp"
#include "ros_healthcare_msg/msg/ecg_leads.hpp"
#include "std_msgs/msg/float64.hpp"

using namespace std;

Gateway::Gateway() 
{
  node = rclcpp::Node::make_shared("gateway");

  hr_pub = node->create_publisher<ros_healthcare_msg::msg::HR>("hr", 10); //rclcpp::SensorDataQoS());
  rr_pub = node->create_publisher<ros_healthcare_msg::msg::RR>("rr", 10); //rclcpp::SensorDataQoS());
  imu_pub = node->create_publisher<sensor_msgs::msg::Imu>("imu", 10); //rclcpp::SensorDataQoS());
  ecg_pub = node->create_publisher<ros_healthcare_msg::msg::ECGLeads>("ecg", 10); //rclcpp::SensorDataQoS());
}

void Gateway::step(const radl_in_t* i, const radl_in_flags_t* i_f, radl_out_t* o, radl_out_flags_t* o_f) 
{
  double hr = i->hr->hr;
  int rr = i->rr->rr;

  if (radl_is_stale(i_f->hr))
    cout << "hr is stale" << endl;
  if (radl_is_timeout(i_f->hr))
    cout << "hr is timeout" << endl;

  if (!radl_is_stale(i_f->hr) && !radl_is_timeout(i_f->hr)) {
    rclcpp::spin_some(node);
    ros_healthcare_msg::msg::HR hr_msg;
    hr_msg.hr = hr;
    hr_pub->publish(hr_msg);
    cout << "HR : " << hr_msg.hr ;
	  if (hr > 98) {
      cout << " <----- HIGH " << endl;
      o->hr_warning->val = true;
    }
    else if (hr < 62) {
      cout << " <----- LOW " << endl;
      o->hr_warning->val = true;
    }
    else {
      cout << endl;
      o->hr_warning->val = false;
    }
  }

  if (radl_is_stale(i_f->rr))
    cout << "rr is stale" << endl;
  if (radl_is_timeout(i_f->rr))
    cout << "rr is timeout" << endl;

  if (!radl_is_stale(i_f->rr) && !radl_is_timeout(i_f->rr)) {
    rclcpp::spin_some(node);
    ros_healthcare_msg::msg::RR rr_msg;
    rr_msg.rr = rr;
    rr_pub->publish(rr_msg);
    cout << "RR : " << rr_msg.rr << endl ;
  }

  if (radl_is_stale(i_f->imu))
    cout << "imu is stale" << endl;
  if (radl_is_timeout(i_f->imu))
    cout << "imu is timeout" << endl;

  if (!radl_is_stale(i_f->imu) && !radl_is_timeout(i_f->imu)) {
    rclcpp::spin_some(node);
    sensor_msgs::msg::Imu imu_msg;
    imu_msg.linear_acceleration.x = i->imu->x;
    imu_msg.linear_acceleration.y = i->imu->y;
    imu_msg.linear_acceleration.z = i->imu->z;
    imu_pub->publish(imu_msg);
    cout << "IMU : (" << imu_msg.linear_acceleration.x << ", " << imu_msg.linear_acceleration.y << ", " << imu_msg.linear_acceleration.z << ")" << endl;
  }

  if (radl_is_stale(i_f->ecg))
    cout << "ecg is stale" << endl;
  if (radl_is_timeout(i_f->ecg))
    cout << "ecg is timeout" << endl;

  if (!radl_is_stale(i_f->ecg) && !radl_is_timeout(i_f->ecg)) {
    rclcpp::spin_some(node);
    ros_healthcare_msg::msg::ECGLeads ecg_msg;
    ros_healthcare_msg::msg::ECGLead ecg_lead;
    ecg_lead.ecg.resize(60);

    for (int j=0; j<60; j++) 
      ecg_lead.ecg[j] = i->ecg->ecg[j];

    ecg_msg.leads.push_back(ecg_lead);
    ecg_pub->publish(ecg_msg);
    cout << "ECG : (" << ecg_msg.leads[0].ecg[0] << ",..., " << ecg_msg.leads[0].ecg[59] << ")" << endl;
  }
}
