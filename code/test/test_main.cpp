#include <unity.h>
#include <Arduino.h>
#include "../include/pi_controller.hpp" // Ensure this header is created and included
#include "../include/p_controller.hpp"

void test_update_function(void) {
    Serial.println("Starting test_update_function");
    PI_Controller controller(0.5, 0.1, 3000, 100);
    controller.init();

    // Test the update function with a reference and actual value
    double ref = 2500;
    double actual = 2000;
    double pwm = controller.update(ref, actual);

    Serial.print("PWM: ");
    Serial.println(pwm);

    // Check if the PWM output is within expected bounds
    TEST_ASSERT_TRUE(pwm > 0);
    TEST_ASSERT_TRUE(pwm <= 255);
    Serial.println("Finished test_update_function");
}

void test_integral_windup(void) {
    PI_Controller controller(0.5, 0.1, 3000, 100);
    controller.init();

    // Test the update function with a reference value beyond max velocity
    double ref = 4000; // Beyond max velocity
    double actual = 2000;
    double pwm = controller.update(ref, actual);

    // Expect saturation and check that integral does not wind up
    TEST_ASSERT_EQUAL(255, pwm);
    double pwm_after = controller.update(ref, actual);
    TEST_ASSERT_EQUAL(255, pwm_after);
}

void setup() {
    Serial.begin(9600); // Initialize serial communication
    delay(2000); // Wait for >2 secs if board doesn't support software reset via Serial.DTR/RTS

    UNITY_BEGIN(); // IMPORTANT LINE!

    RUN_TEST(test_update_function);
    RUN_TEST(test_integral_windup);

    UNITY_END(); // stop unit testing
}

void loop() {
    // Leave empty or add a delay
    delay(500);
}
