/*
 * Created on May, 2014
 * @author: Léonard Gérard leonard.gerard@sri.com
 *
 * Generic code used by radler ROS backend to handle ROS sub and pub.
 *
 * /!\
 * It is important to note that this code is not thread safe. The callbacks
 * (the ::operator() methods) have to be called by the thread of the mbox user.
 * This is done in ROS by using the ros::spinOnce() function.
 * /!\
 *
 */

#pragma once

#include "ros/ros.h"
#include <stdint.h>

namespace radl {

template <typename msg_type>
class Default_sub {
private:
    typedef typename msg_type::ConstPtr msg_ptr;
    msg_ptr mailbox;
    bool stale;

public:
  Default_sub(const msg_ptr& init) {
    this->mailbox = init;
    this->stale = true;
  }
  void operator()(const msg_ptr& msg){
    this->mailbox = msg;
    this->stale = false;
  }
  msg_ptr value(bool *is_stale){
    *is_stale = this->stale;
    this->stale = true;
    return this->mailbox;
  }
};


template <typename msg_type>
class Default_pub {
private:
  ros::Publisher* pub;

public:
  Default_pub(ros::Publisher& pub) {
    this->pub = &pub;
  }
  void operator()(msg_type& msg) {
    this->pub->publish(msg);
  }
};

template <typename msg_type>
class Default_pub_each {
private:
  ros::Publisher* pub;
  const unsigned int each;
  unsigned int each_counter;

public:
  Default_pub_each(ros::Publisher& pub, unsigned int each): each(each), each_counter(0) {
    this->pub = &pub;
  }
  void operator()(msg_type& msg) {
    this->each_counter++;
    if (this->each_counter == this->each) {
      this->pub->publish(msg);
      this->each_counter = 0;
    }
  }
};

}
