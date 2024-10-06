#include "digital_in.hpp"
#include <avr/io.h>

Digital_in::Digital_in(int pin_number) { pin_mask = (1 << pin_number); }

void Digital_in::init() {
  DDRD &= pin_mask; // Data direction register set to input
}

bool Digital_in::is_hi() {
  bool state = (PIND & pin_mask); // Read state
  return state == 1;
}

bool Digital_in::is_lo() {
  bool state = (PIND & pin_mask); // Read state
  return state == 0;
}
