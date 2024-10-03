#include "p_controller.hpp"
#include <Arduino.h>
#include <context.hpp>
#include <encoder_driver.hpp>
#include <init_state.hpp>
#include <motor_driver.hpp>
#include <stdlib.h>

// Transition macros
#define CMD_RESET 'r'
#define CMD_SET_PRE_OP 'p'
#define CMD_SET_OP 'o'

// Control macros
#define VELOCITY_CALCULATION_INTERVAL_MS 1
#define TARGET_VELOCITY 3000
#define MAX_VELOCITY 3350
#define CONTROLLER_UPDATE_RATE_MS 4
#define KP 0.59

// Motor macros
#define C1_PIN 1
#define C2_PIN 2
#define PWM_PIN 0
#define PWM_UPDATE_RATE_MS 0.05

// Motor control variables
P_controller control(KP, MAX_VELOCITY, CONTROLLER_UPDATE_RATE_MS);
Encoder_driver encoder(C1_PIN, C2_PIN, VELOCITY_CALCULATION_INTERVAL_MS);
Motor_driver motor(PWM_PIN, PWM_UPDATE_RATE_MS);

// Global context variables
Context *context;
int pwm_duty_cycle;
volatile float motor_velocity = 0;

int main() {
  int command = 0;
  context = new Context(new Init_state, &control, &encoder, &motor);

  while (1) {
    if (Serial.available() > 0) {
      command = Serial.read();
      switch (command) {
      case CMD_RESET:
        context->reset();
        break;
      case CMD_SET_PRE_OP:
        context->set_pre_op();
        break;
      case CMD_SET_OP:
        context->set_op();
        break;
      }
    }
    delete context;
  }
}

ISR(INT0_vect) { encoder.read_state(); }
ISR(TIMER0_COMPA_vect) {
  motor_velocity = encoder.velocity();
  Serial.print("Current time: ");
  Serial.print("Timestamp: ");
  Serial.print(" s , Reference: ");
  Serial.print(TARGET_VELOCITY);
  Serial.print(" , Actual: ");
  Serial.print(motor_velocity);
  Serial.print(" , PWM: ");
  // Serial.println(pwm);
}
ISR(TIMER1_COMPA_vect) {
  pwm_duty_cycle = control.update(TARGET_VELOCITY, motor_velocity);
  motor.set_duty_cycle(pwm_duty_cycle);
}
ISR(TIMER2_COMPA_vect) { motor.pwm_hi(); }
ISR(TIMER2_COMPB_vect) { motor.pwm_lo(); }
