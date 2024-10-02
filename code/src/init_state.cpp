#include <Arduino.h>
#include <context.hpp>
#include <init_state.hpp>

void Init_state::on_do() {};

void Init_state::on_entry() { Serial.println("Bootup finished"); };

void Init_state::on_exit() {};

void Init_state::on_reset() {};

void Init_state::on_set_pre_op() {};

void Init_state::on_set_op() {};

String Init_state::get_name() { return this->name; };
