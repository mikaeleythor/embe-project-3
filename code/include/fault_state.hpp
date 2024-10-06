#ifndef FAULT_STATE_H

#include <state.hpp>

#define FAULT_STATE_H

class Fault_state : public State {

  void on_do() override;

  void on_entry() override;

  void on_exit() override;

  void on_reset() override;

  void on_set_pre_op() override;

  void on_set_op() override;

	void on_set_fault() override;

  String get_name() override;

  String name = "Fault";
};

#endif // !FAULT_STATE_H
