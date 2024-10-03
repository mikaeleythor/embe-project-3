#include "analog_out.hpp"

Analog_out::Analog_out(int pin_number)
    : pin(Digital_out(pin_number)) {}

void Analog_out::init(float period_ms, int timer_num) {
	timer = new Timer_msec(period_ms, 0, timer_num);
  timer->init();
  pin.init();
}

void Analog_out::set(int duty_cycle, int timer_num) {
  timer->set_duty_cycle(duty_cycle);
}
