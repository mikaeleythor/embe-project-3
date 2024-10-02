#include "digital_in.h"
#include <avr/io.h>

Digital_in::Digital_in(int pin_number) { pin_mask = (1 << pin_number); }

void Digital_in::init() {
  DDRB &= pin_mask; // Data direction register set to input
}

bool Digital_in::is_hi() {
  bool state = (PINB & pin_mask); // Read state
  return state == 1;
}

bool Digital_in::is_lo() {
  bool state = (PINB & pin_mask); // Read state
  return state == 0;
}
