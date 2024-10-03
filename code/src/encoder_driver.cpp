#include "encoder_driver.hpp"
#include "avr/interrupt.h"
#include "avr/io.h"
#include <util/delay.h>

#define ENCODER_TIMER_NUM 0

Encoder_driver::Encoder_driver(int c1_, int c2_, int resolution_ms)
    : led(Digital_out(5)), pos_encoder(Digital_in(c1_)),
      dir_encoder(Digital_in(c2_)), pos_pin_state(0), pos(0), last_pos(0),
      pulse_count(0), resolution_ms(resolution_ms), vel(0), timer(Timer_msec()) {}

void Encoder_driver::init() {
  led.init();
  timer.init(resolution_ms, 0, ENCODER_TIMER_NUM); // Init timer to interrupt with no duty cycle

  // TODO: Generalize hardcoded external interrupt setup
  DDRD &= (1 << DDD1);
  PORTD |= (1 << PORTD2);
  EICRA |= (1 << ISC00);
  EIMSK |= (1 << INT0);
  sei();
}

void Encoder_driver::read_state() {
	led.toggle();
  bool new_pos_pin_state = pos_encoder.is_hi(); // 1 if high, 0 if low

  bool new_dir_pin_state = dir_encoder.is_hi(); // 1 if high, 0 if low
  bool pos_changed = new_pos_pin_state != pos_pin_state;
  if (pos_changed) {
    // Increment pulse counter
    pulse_count++;
    // Define forward motion as direction and position states being at odds
    bool forward_motion = new_dir_pin_state != new_pos_pin_state;
    if (forward_motion) {
      pos++;
    } else
      pos--;
    pos_pin_state = new_pos_pin_state;
  }
}

int Encoder_driver::position() { return pos; }

int Encoder_driver::count() { return pulse_count; }

/**
 * Calculates the velocity of the encoder driver in edges per second.
 *
 * This function calculates the velocity of the encoder driver by measuring the
 * change in position over a specified time interval.
 *
 * @return The velocity of the encoder driver in edges per second.
 */
float Encoder_driver::velocity() {
  float edges_per_ms = (float)(pos - last_pos) / resolution_ms;
  last_pos = pos; // Update reference position to current position
	vel = edges_per_ms * 1000; // Update velocity
  return vel;
}
