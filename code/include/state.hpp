#ifndef STATE_H
#define STATE_H
#include <Arduino.h>
// Forward declaration
class Context;

class State {
protected:
  Context *context_;

public:
  virtual ~State() {}

  void set_context(Context *context) { this->context_ = context; }

  virtual void on_do() = 0;

  virtual void on_entry() = 0;

  virtual void on_exit() = 0;

  virtual void on_reset() = 0;

  virtual void on_set_pre_op() = 0;

  virtual void on_set_op() = 0;

  virtual String get_name() = 0;

  String name = "Base";
};

#endif // STATE_H
