#ifndef TIMER_MSEC_H
#define TIMER_MSEC_H
#pragma once

class Timer_msec {
public:
  Timer_msec();
  void init(int period_ms, int duty_cycle, int timer_num = 1);
  void set_duty_cycle(int duty_cycle, int timer_num = 1);

private:
};
#endif // !TIMER_MSEC_H
