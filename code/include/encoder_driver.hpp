#ifndef ENCODER_DRIVER_H
#define ENCODER_DRIVER_H
#include "digital_in.hpp"
#include "digital_out.hpp"
#include "timer_msec.hpp"

class Encoder_driver {
public:
  Encoder_driver(int c1, int c2, int resolution_ms);
  ~Encoder_driver();
  int position();
  int count();
  void read_state();
  void init();
  float velocity();

private:
  Digital_in pos_encoder;
  Digital_in dir_encoder;
  int pos_pin_state; // State of position pin
  int pos;           // Diff in position since init
  int last_pos;      // Reference used to calculate velocity
  int pulse_count;
  int resolution_ms;
  int vel;
  Digital_out *led;
  Timer_msec *timer;
};
#endif // ENCODER_DRIVER_H
