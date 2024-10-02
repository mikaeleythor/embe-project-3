#include "p_controller.hpp"
#include <Arduino.h>
#include <context.hpp>
#include <encoder_driver.hpp>
#include <init_state.hpp>
#include <motor_driver.hpp>
#include <stdlib.h>

// Transition macros
#define RESET 'r'
#define SET_PRE_OP 'p'
#define SET_OP 'o'

#define SLEEP_TIME_MS 200

// Global motor control variables
P_controller control(0.59, 3350);
Encoder_driver encoder(1, 2, SLEEP_TIME_MS);
Motor_driver motor(0);

int pwm;
int s = 0;
volatile float vel = 0;

// Global context variables
Context *context;
int command = 0;

int main() {
  init();
  Serial.begin(9600); // Open serial port with baud rate 9600
  Serial.flush();

  context = new Context(new Init_state);

  encoder.init();
  motor.init(5);
  motor.set_duty_cycle(90, 0);

  while (1) {
    if (Serial.available() > 0) {
      command = Serial.read();

      switch (command) {
      case RESET:
        context->reset();
        break;
      case SET_PRE_OP:
        context->set_pre_op();
        break;
      case SET_OP:
        context->set_op();
        break;
      }
    }
    delete context;
  }
}

ISR(INT0_vect) { encoder.read_state(); }
ISR(TIMER1_COMPA_vect) {
  s++;
  vel = encoder.velocity();
  Serial.print("Current time: ");
  Serial.print("Timestamp: ");
  Serial.print(s);
  Serial.print(" s , Reference: ");
  Serial.print(3000);
  Serial.print(" , Actual: ");
  Serial.print(vel);
  Serial.print(" , PWM: ");
  Serial.println(pwm);
}
ISR(TIMER0_COMPA_vect) { motor.pwm_hi(); }
ISR(TIMER0_COMPB_vect) { motor.pwm_lo(); }
