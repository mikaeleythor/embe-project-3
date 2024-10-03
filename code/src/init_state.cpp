#include "pre_op_state.hpp"
#include <Arduino.h>
#include <context.hpp>
#include <encoder_driver.hpp>
#include <init_state.hpp>
#include <motor_driver.hpp>

extern Encoder_driver encoder;
extern Motor_driver motor;

void Init_state::on_do() {};

void Init_state::on_entry() {
	// Initialize Serial
  init();
  Serial.begin(9600); // Open serial port with baud rate 9600
  Serial.flush();

	// TODO: Split initialization and start
  encoder.init();
  motor.init(5);
  motor.set_duty_cycle(90, 0);

  Serial.println("Bootup finished");
  this->context_->transition_to(new Pre_op_state);
};

void Init_state::on_exit() {};

void Init_state::on_reset() {};

void Init_state::on_set_pre_op() {};

void Init_state::on_set_op() {};

String Init_state::get_name() { return this->name; };
