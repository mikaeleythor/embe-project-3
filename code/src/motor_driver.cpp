#include <analog_out.hpp>
#include "motor_driver.hpp"
#include "p_controller.hpp"
#define PWM_TIMER_NUM 2

Motor_driver::Motor_driver(int pin_number, float pwm_update_rate, P_controller* controller)
    : pwm(Analog_out(pin_number)), pwm_update_rate_ms(pwm_update_rate), controller(controller) {}

void Motor_driver::init() { pwm.init(pwm_update_rate_ms, PWM_TIMER_NUM); }

void Motor_driver::set_duty_cycle(int duty_cycle, int timer_num) {
    this->duty_cycle = duty_cycle;
    pwm.set(duty_cycle, timer_num);
    // Use controller to determine direction
    if (duty_cycle > 0) {
        // Forward direction
        pwm_hi();
    } else {
        // Reverse direction
        pwm_lo();
    }
}

int Motor_driver::get_duty_cycle() { return this->duty_cycle; }

void Motor_driver::pwm_hi() { pwm.pin.set_hi(); }

void Motor_driver::pwm_lo() { pwm.pin.set_lo(); }
