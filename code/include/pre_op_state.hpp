#ifndef PRE_OP_STATE_H

#include <state.hpp>

#define PRE_OP_STATE_H

class Pre_op_state : public State {
  void on_do() override;

  void on_entry() override;

  void on_exit() override;

  void on_reset() override;

  void on_set_pre_op() override;

  void on_set_op() override;

	void on_set_fault() override;

  String get_name() override;

  String name = "Pre-operational";
};

#endif // !PRE_OP_STATE_H
