
#include <Arduino.h>
#include <context.hpp>
#include <init_state.hpp>
#include <op_state.hpp>
#include <pre_op_state.hpp>
#include "motor_driver.hpp"
#include "constants.hpp"
extern volatile bool is_op;
extern volatile double motor_velocity;
extern volatile double pwm_duty_cycle;

void Op_state::on_do() {

}

void Op_state::on_entry() {
	this->context_->led->set_mode(ALWAYS_ON);
	is_op = true;
	this->context_->motor->set_duty_cycle(90, 0);
};

void Op_state::on_exit() {
    is_op = false;
    Serial.println("Exiting Operational State");
    // Stop motor or perform cleanup
    this->context_->motor->set_duty_cycle(0, 0); // Stop the motor
}

void Op_state::on_reset() { this->context_->transition_to(new Init_state); }

void Op_state::on_set_pre_op() {
    this->context_->transition_to(new Pre_op_state);
}

void Op_state::on_set_op() {}

String Op_state::get_name() { return this->name; }
