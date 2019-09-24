#include "talker.h" 
#include "race/drive_values.h"

using namespace std;

Talker::Talker()
{
  pub = h.advertise<race::drive_values>("/drive_pwm", 1);
}

int arduino_map (double x, int in_min, int in_max, int out_min, int out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void Talker::step(const radl_in_t * in, const radl_in_flags_t* inflags, radl_out_t * out, radl_out_flags_t* outflags)
{
  double velocity = in->drive_parameters->velocity;
  double angle = in->drive_parameters->angle;
  cout << "Velocity: " << velocity << ", Angle: " << angle << endl;

  int pwm1 = arduino_map(velocity,-100,100,6554,13108);
  int pwm2 = arduino_map(angle,-100,100,6554,13108);
  cout << "PWM_drive: " << pwm1 << ", PWM_angle: " << pwm2 << endl;

  race::drive_values msg;
  msg.pwm_drive = pwm1;
  msg.pwm_angle = pwm2;
  pub.publish(msg);
}
