#ifndef P_CONTROLLER_H
#define P_CONTROLLER_H

class P_controller {
private:
    double Kp;  // Proportional gain
    double max_velocity;  // Maximum velocity in edges per second

public:
    // Constructor to initialize Kp and the max_velocity (max possible speed in edges/sec)
    P_controller(double Kp_, double max_velocity_);

    // Function to compute control law and scale it to a valid PWM range
    double update(double ref, double actual);
};

#endif  // P_CONTROLLER_H