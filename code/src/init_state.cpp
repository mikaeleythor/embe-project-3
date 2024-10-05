#include "pre_op_state.hpp"
#include <Arduino.h>
#include <context.hpp>
#include <encoder_driver.hpp>
#include <init_state.hpp>
#include <motor_driver.hpp>
#include <led_blinker.hpp>

// Control macros
#define VELOCITY_UPDATE_RATE_MS 4
#define MAX_VELOCITY 3350
#define CONTROLLER_UPDATE_RATE_MS 4
#define KP 0.59

// Motor macros
#define LED_PIN 5
#define C1_PIN 1
#define C2_PIN 2
#define PWM_PIN 0
#define PWM_UPDATE_RATE_MS 1

#define LED_TIMER_INTERVAL_MS 250

void Init_state::init_() {
  init();             // Initialize Arduino library
  Serial.begin(9600); // Open serial port with baud rate 9600
  Serial.flush();     // Flush serial buffer

#ifdef DEBUG
  Serial.println("Serial initialization finished");
#endif // DEBUG

  // Instantiate context components
  this->context_->encoder =
      new Encoder_driver(C1_PIN, C2_PIN, VELOCITY_UPDATE_RATE_MS);
  this->context_->motor = new Motor_driver(PWM_PIN, PWM_UPDATE_RATE_MS, this->context_->control);
  this->context_->control =
      new P_controller(KP, MAX_VELOCITY, CONTROLLER_UPDATE_RATE_MS);
	this->context_->led = new Led_blinker(LED_TIMER_INTERVAL_MS, 0);

#ifdef DEBUG
  Serial.println("Context component instantiation finished");
#endif // DEBUG

  // Initialize context components
  this->context_->encoder->init();
  this->context_->motor->init();
  this->context_->control->init();

#ifdef DEBUG
  Serial.println("Context component initialization finished");
#endif // DEBUG
};

void Init_state::cleanup() {
  delete this->context_->encoder;
  delete this->context_->motor;
  delete this->context_->control;
  this->context_->encoder = nullptr;
  this->context_->motor = nullptr;
  this->context_->control = nullptr;
};
void Init_state::on_do() {};

void Init_state::on_entry() {
  this->cleanup();
  this->init_();
  this->context_->transition_to(new Pre_op_state);
};

void Init_state::on_exit() { Serial.println("Bootup finished"); };

void Init_state::on_reset() {};

void Init_state::on_set_pre_op() {};

void Init_state::on_set_op() {};

String Init_state::get_name() { return this->name; };
