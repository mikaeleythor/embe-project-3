#include "pi_controller.hpp"
#include "constants.hpp" // Include the constants header

PI_Controller::PI_Controller(double Kp_, double Ki_, double max_velocity_, int update_rate_ms_)
    : P_controller(Kp_, max_velocity_, update_rate_ms_), Ki(Ki_), integral(0) {}

void PI_Controller::init() {
    P_controller::init();
    integral = 0; // Reset integral on initialization
}

double PI_Controller::update(double ref, double actual) {
    double error = ref - actual;
    integral += error * (P_controller::getUpdateRateMs() / 1000.0); // Scale by time step

    // Use the global KP and TI values
    double control_signal = KP * error + (KI / TI) * integral;

    return applySaturation(control_signal, error);
}

double PI_Controller::applySaturation(double control_signal, double error) {
    if (control_signal > 255) {
        control_signal = 255;
        integral -= error * (P_controller::getUpdateRateMs() / 1000.0); // Prevent windup
    } else if (control_signal < 0) {
        control_signal = 0;
        integral -= error * (P_controller::getUpdateRateMs() / 1000.0); // Prevent windup
    }
    return control_signal;
}
