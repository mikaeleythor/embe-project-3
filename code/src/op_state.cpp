#include <context.hpp>
#include <init_state.hpp>
#include <op_state.hpp>
#include <pre_op_state.hpp>

void Op_state::on_do() {};

void Op_state::on_entry() {
  this->context_->motor->set_duty_cycle(90, 0);
};

void Op_state::on_exit() {};

void Op_state::on_reset() { this->context_->transition_to(new Init_state); };

void Op_state::on_set_pre_op() { this->context_->transition_to(new Pre_op_state); };

void Op_state::on_set_op() {};

String Op_state::get_name() { return this->name; };
