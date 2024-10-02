#ifndef OP_STATE_H

#include <state.hpp>

#define OP_STATE_H

class Op_state : public State {
  void on_do() override;

  void on_entry() override;

  void on_exit() override;

  void on_reset() override;

  void on_set_pre_op() override;

  void on_set_op() override;

  String get_name() override;

  String name = "Operational";
};

#endif // !OP_STATE_H
