#ifndef INIT_STATE_H

#include <state.hpp>

#define INIT_STATE_H

// Control macros
#define VELOCITY_UPDATE_RATE_MS 4
#define MAX_VELOCITY 3350
#define CONTROLLER_UPDATE_RATE_MS 4
#define KP 0.59

// Motor macros
#define LED_PIN 5
#define C1_PIN 1
#define C2_PIN 2
#define PWM_PIN 0
#define PWM_UPDATE_RATE_MS 1
#define BUTTON_PIN 7

#define LED_TIMER_INTERVAL_MS 250
#define LED_2HZ_BAND 1
#define LED_1HZ_BAND 2

class Init_state : public State {

  void init_components();

  void cleanup();

  void on_do() override;

  void on_entry() override;

  void on_exit() override;

  void on_reset() override;

  void on_set_pre_op() override;

  void on_set_op() override;

	void on_set_fault() override;

  String get_name() override;

  String name = "Init";
};

#endif // !INIT_STATE_H
