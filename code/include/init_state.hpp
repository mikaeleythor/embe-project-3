#ifndef INIT_STATE_H

#include <state.hpp>

#define INIT_STATE_H

class Init_state : public State {
  void on_do() override;

  void on_entry() override;

  void on_exit() override;

  void on_reset() override;

  void on_set_pre_op() override;

  void on_set_op() override;

  String get_name() override;

  String name = "Init";
};

#endif // !INIT_STATE_H
