#include <context.hpp>
#include <fault_state.hpp>
#include <init_state.hpp>
#include <op_state.hpp>
#include <pre_op_state.hpp>

extern volatile bool is_op;

void Fault_state::on_do() {}

void Fault_state::on_entry() {
  this->context_->led->set_bandwidth(LED_2HZ_BAND);
  this->context_->led->set_mode(BLINK);
  is_op = false;
}

void Fault_state::on_exit() {}

void Fault_state::on_reset() { this->context_->transition_to(new Init_state); }

void Fault_state::on_set_pre_op() {
  this->context_->transition_to(new Pre_op_state);
}

void Fault_state::on_set_op() { this->context_->transition_to(new Op_state); }

void Fault_state::on_set_fault() {}

String Fault_state::get_name() { return this->name; }
