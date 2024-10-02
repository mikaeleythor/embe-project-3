#include "digital_out.h"
#include <avr/io.h>

Digital_out::Digital_out(int pin_number) { pinMask = (1 << pin_number); }

void Digital_out::init() { DDRB |= pinMask; }

void Digital_out::set_hi() { PORTB |= pinMask; }

void Digital_out::set_lo() { PORTB &= ~pinMask; }

void Digital_out::toggle() { PORTB ^= pinMask; }
