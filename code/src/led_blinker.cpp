#include <Arduino.h>
#include <led_blinker.hpp>

// #define DEBUG

Led_blinker::Led_blinker(int timer_interval_ms,
                         int bandwidth_in_timer_intervals)
    : timer_interval_ms(timer_interval_ms),
      bandwidth(bandwidth_in_timer_intervals), interval_count(0), mode(0),
      led(nullptr), timer(nullptr) {}

void Led_blinker::init() {
  this->led = new Digital_out(LED_PIN);
  this->led->init();
  this->timer = new Timer_msec(this->timer_interval_ms, 0, LED_TIMER_NUM);
  this->timer->init();
#ifdef DEBUG
  Serial.println("Led timer initialization finished with ms: " +
                 String(this->timer_interval_ms));
#endif // DEBUG
}

void Led_blinker::set_bandwidth(int timer_intervals) {
  this->bandwidth = timer_intervals;
}

void Led_blinker::next_interval() {
  this->interval_count++;
  if (this->interval_count == this->bandwidth) {
    this->led->toggle();
    this->interval_count = 0;
  }
}

void Led_blinker::set_mode(int mode) { this->mode = mode; }

void Led_blinker::handle_interval() {
  switch (this->mode) {
  default:
    break;
  case ALWAYS_ON:
    this->led->set_hi();
    break;
  case ALWAYS_OFF:
    this->led->set_lo();
    break;
  case BLINK:
    this->next_interval();
    break;
  }
}

Led_blinker::~Led_blinker() {
  delete led;
  delete timer;
}
