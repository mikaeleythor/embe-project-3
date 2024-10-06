#ifndef CONTEXT_H
#define CONTEXT_H
#include "p_controller.hpp"
#include <encoder_driver.hpp>
#include <led_blinker.hpp>
#include <motor_driver.hpp>
#include <state.hpp>

class Context {
  /**
   * @var State A reference to the current state of the Context.
   */
public:
  P_controller *control;
  Encoder_driver *encoder;
  Motor_driver *motor;
  Led_blinker *led;
  Digital_in *button;

private:
  State *state_;

public:
  Context(State *state)
      : control(nullptr), encoder(nullptr), motor(nullptr), led(nullptr),
        button(nullptr), state_(nullptr) {
    this->transition_to(state);
  }

  ~Context() {
    delete state_;
    delete control;
    delete encoder;
    delete motor;
    delete led;
  }

  /**
   * The Context allows changing the State object at runtime.
   */

  void transition_to(State *state) {
    Serial.println("State changed to " + state->get_name());
    if (this->state_ != nullptr) {
      this->state_->on_exit();
      delete this->state_;
    }

    this->state_ = state;

    this->state_->set_context(this);

    this->state_->on_entry();
  }

  /**
   * The Context delegates part of its behavior to the current State object.
   */

  // void do_work() { this->state_->on_do(); }
  void reset() { this->state_->on_reset(); }
  void set_pre_op() { this->state_->on_set_pre_op(); }
  void set_op() { this->state_->on_set_op(); }
  void set_fault() { this->state_->on_set_fault(); }
};
#endif // CONTEXT_H
