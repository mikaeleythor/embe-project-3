#ifndef ANALOG_OUT_H
#define ANALOG_OUT_H

#include <digital_out.hpp>
#include <timer_msec.hpp>

class Analog_out {
public:
  Analog_out(int pin_number);
  void init(float period_ms = 1000, int timer_num = 0);
  void set(int duty_cycle, int timer_num = 0);

private:
  Timer_msec *timer;

public:
  Digital_out pin;
};

#endif // ANALOG_OUT_H
