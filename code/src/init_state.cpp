#include "pre_op_state.hpp"
#include <Arduino.h>
#include <context.hpp>
#include <encoder_driver.hpp>
#include <init_state.hpp>
#include <fault_state.hpp>
#include <led_blinker.hpp>
#include <motor_driver.hpp>

void Init_state::init_components() {
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
  this->context_->button = new Digital_in(BUTTON_PIN);

#ifdef DEBUG
  Serial.println("Context component instantiation finished");
#endif // DEBUG

  // Initialize context components
  this->context_->encoder->init();
  this->context_->motor->init();
  this->context_->control->init();
  this->context_->led->init();
  this->context_->button->init();

#ifdef DEBUG
  Serial.println("Context component initialization finished");
#endif // DEBUG
};

void Init_state::cleanup() {
  delete this->context_->encoder;
  delete this->context_->motor;
  delete this->context_->control;
  delete this->context_->led;
  delete this->context_->button;
  this->context_->encoder = nullptr;
  this->context_->motor = nullptr;
  this->context_->control = nullptr;
  this->context_->led = nullptr;
  this->context_->button = nullptr;
};
void Init_state::on_do() {};

void Init_state::on_entry() {
  if (this->context_->led != nullptr)
    this->context_->led->set_mode(ALWAYS_OFF);
  this->cleanup();
  this->init_components();
  this->context_->transition_to(new Pre_op_state);
};

void Init_state::on_exit() { Serial.println("Bootup finished"); };

void Init_state::on_reset() {};

void Init_state::on_set_pre_op() {};

void Init_state::on_set_op() {};

void Init_state::on_set_fault() {
  this->context_->transition_to(new Fault_state);
};

String Init_state::get_name() { return this->name; };
