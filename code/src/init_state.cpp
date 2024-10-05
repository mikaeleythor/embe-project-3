#include "pre_op_state.hpp"
#include <Arduino.h>
#include <context.hpp>
#include <encoder_driver.hpp>
#include <init_state.hpp>
#include <motor_driver.hpp>

// Control macros
#define VELOCITY_UPDATE_RATE_MS 1
#define MAX_VELOCITY 3350
#define CONTROLLER_UPDATE_RATE_MS 4
#define KP 0.59

// Motor macros
#define C1_PIN 1
#define C2_PIN 2
#define PWM_PIN 0
#define PWM_UPDATE_RATE_MS 0.05

void Init_state::on_do() {};

void Init_state::on_entry() {
  // Initialize Serial
  init(); // Initialize Arduino library
  Serial.begin(9600); // Open serial port with baud rate 9600
  Serial.flush(); // Flush serial buffer

	// Motor control variables
	this->context_->control = new P_controller(KP, MAX_VELOCITY, CONTROLLER_UPDATE_RATE_MS);
	this->context_->encoder = new Encoder_driver(C1_PIN, C2_PIN, VELOCITY_UPDATE_RATE_MS);
	this->context_->motor = new Motor_driver(PWM_PIN, PWM_UPDATE_RATE_MS);

  this->context_->encoder->init();
  this->context_->motor->init();
	this->context_->control->init();

  Serial.println("Bootup finished");
  this->context_->transition_to(new Pre_op_state);
};

void Init_state::on_exit() {};

void Init_state::on_reset() {};

void Init_state::on_set_pre_op() {};

void Init_state::on_set_op() {};

String Init_state::get_name() { return this->name; };
