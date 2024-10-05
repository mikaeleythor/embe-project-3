#include "p_controller.hpp"

#define CONTROL_TIMER_NUM 0

P_controller::P_controller(double Kp_, double max_velocity_,
                           int update_rate_ms_)
    : Kp(Kp_), max_velocity(max_velocity_), update_rate_ms(update_rate_ms_) {}

double P_controller::update(double ref, double actual) {
  double error = ref - actual;

  double control_signal = Kp * error;

  double pwm = (control_signal / max_velocity) * 255;

  if (pwm < 0)
    pwm = 0;
  if (pwm > 255)
    pwm = 255;

  return pwm;
}

void P_controller::init() {
  timer = new Timer_msec(update_rate_ms, 0, CONTROL_TIMER_NUM);
  timer->init();
}

P_controller::~P_controller() { delete timer; }
