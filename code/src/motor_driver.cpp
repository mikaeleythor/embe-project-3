#include <analog_out.hpp>
#include <motor_driver.hpp>

#define PWM_TIMER_NUM 2

Motor_driver::Motor_driver(int pin_number) : pwm(Analog_out(pin_number)) {}

void Motor_driver::init(int period_ms) { pwm.init(period_ms, PWM_TIMER_NUM); }

void Motor_driver::set_duty_cycle(int duty_cycle, int timer_num) {
  pwm.set(duty_cycle, timer_num);
}

void Motor_driver::pwm_hi() { pwm.pin.set_hi(); }

void Motor_driver::pwm_lo() { pwm.pin.set_lo(); }
