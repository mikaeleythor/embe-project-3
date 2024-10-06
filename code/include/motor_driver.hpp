#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H
#include <analog_out.hpp>
#include "p_controller.hpp" // Ensure this is included

class Motor_driver {
public:
	Motor_driver(int pin_number, float pwm_update_rate, P_controller* controller);
	void init();
	void set_duty_cycle(int duty_cycle,int timer_num=0);
	void pwm_hi();
	void pwm_lo();
	int get_duty_cycle();

private:
	Analog_out pwm;
	int duty_cycle;
	float pwm_update_rate_ms;
	P_controller* controller;
};
#endif // !MOTOR_DRIVER_H
