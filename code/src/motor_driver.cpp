#include <analog_out.h>
#include <motor_driver.h>

Motor_driver::Motor_driver(int pin_number) : pwm(Analog_out(pin_number)) {}

void Motor_driver::init(int period_ms) {
	pwm.init(period_ms);
}

void Motor_driver::set_duty_cycle(int duty_cycle,int timer_num) {
  pwm.set(duty_cycle,timer_num);
}

void Motor_driver::pwm_hi() {
  pwm.pin.set_hi();
}

void Motor_driver::pwm_lo() {
  pwm.pin.set_lo();
}
