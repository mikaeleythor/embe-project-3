#ifndef TIMER_MSEC_H
#define TIMER_MSEC_H
#pragma once

class Timer_msec {
public:
  Timer_msec(float period_ms, int duty_cycle, int timer_num = 1);
  void init();
  void set_duty_cycle(int duty_cycle);

private:
  int timer_num;
  int period_ms;
  int duty_cycle;
};
#endif // !TIMER_MSEC_H
