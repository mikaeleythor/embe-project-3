#ifndef PI_CONTROLLER_H
#define PI_CONTROLLER_H

#include "p_controller.hpp"

class PI_Controller : public P_controller {
private:
    double Ki;           // Integral gain
    double integral;     // Integral of the error

    // New method to handle saturation and prevent windup
    double applySaturation(double control_signal, double error);

public:
    PI_Controller(double Kp_, double Ki_, double max_velocity_, int update_rate_ms_);
    void init(); // Remove 'override' if not virtual
    double update(double ref, double actual); // Remove 'override' if not virtual
};

#endif // PI_CONTROLLER_H
