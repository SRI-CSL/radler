#include "controller.h"
#include <ncurses.h>
#include <iostream>

using namespace std;

double prev_speed = 0.0;
double prev_angle = 0.0;
double prev_error = 0.0;

void Controller::step(const radl_in_t * in, const radl_in_flags_t* iflags, radl_out_t * out, radl_out_flags_t* oflags)
{
  double speed;
  double angle; 

  // teleop
  if ( !radl_is_stale(iflags->teleop) && !radl_is_timeout(iflags->teleop) ) {  
    switch (in->teleop->value) { 
      case KEY_UP:
        speed = prev_speed + 0.1;
        angle = prev_angle;
        cout << "Speed UP       ";
        break;
      case KEY_DOWN:
        speed = prev_speed - 0.1;
        angle = prev_angle;
        cout << "Speed DOWN     ";
        break;
      case KEY_RIGHT:
        speed = prev_speed;
        angle = prev_angle + 0.1;
        cout << "Turn RIGHT     ";
        break;
      case KEY_LEFT:
        speed = prev_speed;
        angle = prev_angle - 0.1;
        cout << "Turn LEFT      ";
        break;
      default: 
        speed = 0.0;
        angle = 0.0;
        cout << "RESET          ";
        break;
    }
  }
  // pid_controller 
  else {
    double error = in->error->value;

    speed = *RADL_THIS->vel_input;
    angle = *RADL_THIS->kp * error + *RADL_THIS->kd * (error - prev_error);
    angle += *RADL_THIS->servo_offset;

    prev_error = error;

    if (abs(speed) < *RADL_THIS->esc_sensitivity) {
      if (speed > 0) 
        speed = *RADL_THIS->esc_sensitivity;
      else if (speed < 0)  
        speed -= *RADL_THIS->esc_sensitivity;
    }
    if (abs(angle) < *RADL_THIS->servo_sensitivity) {
      if (angle > 0) 
        angle = *RADL_THIS->servo_sensitivity;
      else if (angle < 0) 
        angle -= *RADL_THIS->servo_sensitivity;
    }
  }
 
  if (abs(speed) > *RADL_THIS->max_speed) {
    if (speed > 0) 
      speed = *RADL_THIS->max_speed;
    else 
      speed -= *RADL_THIS->max_speed;
  }
  if (angle > 100) {
    angle = 100;
  }
  if (angle < -100) {
    angle = -100;
  }

  prev_speed = speed;
  prev_angle = angle;
  out->drive_parameters->velocity = speed;
  out->drive_parameters->angle = angle;
  cout << "Velocity: " << out->drive_parameters->velocity << ", Angle: " << out->drive_parameters->angle  << endl;
}
