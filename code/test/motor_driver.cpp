#include <analog_out.hpp>
#include <motor_driver.hpp>

#define PWM_TIMER_NUM 2

Motor_driver::Motor_driver(int pin_number, float pwm_update_rate)
    : pwm(Analog_out(pin_number)), pwm_update_rate_ms(pwm_update_rate) {}

void Motor_driver::init() { pwm.init(pwm_update_rate_ms, PWM_TIMER_NUM); }

void Motor_driver::set_duty_cycle(int duty_cycle, int timer_num) {
  pwm.set(duty_cycle, timer_num);
}

void Motor_driver::pwm_hi() { pwm.pin.set_hi(); }

void Motor_driver::pwm_lo() { pwm.pin.set_lo(); }
