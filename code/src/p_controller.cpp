#include "p_controller.hpp"

P_controller::P_controller(double Kp_, double max_velocity_) : Kp(Kp_), max_velocity(max_velocity_) {}

double P_controller::update(double ref, double actual) {
    double error = ref - actual;

    double control_signal = Kp * error;

    double pwm = (control_signal / max_velocity) * 255;

    if (pwm < 0) pwm = 0;
    if (pwm > 255) pwm = 255;
    

    return pwm;
}
