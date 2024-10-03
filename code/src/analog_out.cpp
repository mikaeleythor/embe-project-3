#include "analog_out.hpp"

Analog_out::Analog_out(int pin_number)
    : timer(Timer_msec()), pin(Digital_out(pin_number)) {}

void Analog_out::init(int period_ms, int timer_num) {
  timer.init(period_ms, 0, timer_num);
  pin.init();
}

void Analog_out::set(int duty_cycle, int timer_num) {
  timer.set_duty_cycle(duty_cycle, timer_num);
}
