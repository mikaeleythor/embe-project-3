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

#define TARGET_VELOCITY 3000

// Global context variables
Context *context;
int pwm_duty_cycle;
volatile float motor_velocity = 0;
volatile bool is_op = false;

int main() {
  int command = 0;
  context = new Context(new Init_state);

  while (1) {
    if (context->button->is_hi()) {
      context->set_fault();
    }
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
  }
  delete context;
}

ISR(INT0_vect) { context->encoder->read_state(); }
ISR(TIMER0_COMPA_vect) {
  if (is_op) {
    motor_velocity = context->encoder->velocity();
    pwm_duty_cycle = context->control->update(TARGET_VELOCITY, motor_velocity);
    context->motor->set_duty_cycle(pwm_duty_cycle);
  }
}
ISR(TIMER1_COMPA_vect) { context->led->handle_interval(); }
ISR(TIMER2_COMPA_vect) {
  if (is_op)
    context->motor->pwm_hi();
}
ISR(TIMER2_COMPB_vect) {
  if (is_op)
    context->motor->pwm_lo();
}
