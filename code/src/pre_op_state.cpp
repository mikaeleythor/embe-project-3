#include <context.hpp>
#include <init_state.hpp>
#include <op_state.hpp>
#include <pre_op_state.hpp>

void Pre_op_state::on_do() {};

void Pre_op_state::on_entry() {};

void Pre_op_state::on_exit() {};

void Pre_op_state::on_reset() {
  this->context_->transition_to(new Init_state);
};

void Pre_op_state::on_set_pre_op() {};

void Pre_op_state::on_set_op() { this->context_->transition_to(new Op_state); };

String Pre_op_state::get_name() { return this->name; };
