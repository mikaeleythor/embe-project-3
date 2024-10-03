#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H
#include <analog_out.hpp>

class Motor_driver {
public:
	Motor_driver(int pin_number, float pwm_update_rate);
	void init();
	void set_duty_cycle(int duty_cycle,int timer_num=0);
	void pwm_hi();
	void pwm_lo();
private:
	Analog_out pwm;
	float pwm_update_rate_ms;
};
#endif // !MOTOR_DRIVER_H
