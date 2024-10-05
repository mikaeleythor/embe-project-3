#ifndef LED_BLINKER_H
#define LED_BLINKER_H

#include "digital_out.hpp"
#include "timer_msec.hpp"

#define LED_PIN 5
#define LED_TIMER_NUM 0

#define ALWAYS_ON 0
#define ALWAYS_OFF 1
#define BLINK 2

class Led_blinker {
public:
  Led_blinker(int timer_interval_ms, int bandwidth_in_timer_intervals);
  ~Led_blinker();
  void init();

  /* If a timer interval is 1s and timer_intervals_per_edge is 1,
   * then the LED will change states at 1Hz. If timer_intervals_per_edge is 2,
   * then the LED will change states at 0.5Hz
   * */
  void update_bandwidth(int timer_intervals);

	void handle_interval();

private:
  int timer_interval_ms;
  int bandwidth;
  int interval_count;
	int mode;
  Digital_out *led;
  Timer_msec *timer;

  /* Updates the count of intervals since last change, toggles LED state and
   * resets counter if updated count is equal to bandwidth */
  void next_interval();

  void set_mode(int mode);

};
#endif
