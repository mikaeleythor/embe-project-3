#include <avr/interrupt.h>
#include <timer_msec.hpp>

Timer_msec::Timer_msec() {}

void Timer_msec::init(int period_ms, int duty_cycle, int timer_num) {
  switch (timer_num) {
  default:
    break;
  case 0:
    // Set the Timer Mode to CTC
    TCCR0A |= (1 << WGM01);
    // Set the value that you want to count to
    OCR0A = (16000000 / 256 - 1) / 1000 * period_ms;
    TIMSK0 |= (1 << OCIE0A); // Set the ISR COMPA vect
    if (duty_cycle > 0) {
      set_duty_cycle(duty_cycle, timer_num);
    }
    sei();                   // enable interrupts
    TCCR0B |= (1 << CS02);
    // set prescaler to 256 and start the timer
    break;
  case 1:
    // this code sets up timer1 for a 1s @ 16Mhz Clock (mode 4)
    // counting 16000000/1024 cycles of a clock prescaled by 1024
    TCCR1A = 0; // set timer1 to normal operation (all bits in control registers
                // A and B set to zero)
    TCCR1B = 0; //
    TCNT1 = 0;  // initialize counter value to 0
    // assign target count to compare register A (must be less than 65536)
    OCR1A = (16000000 / 1024 - 1) / 1000 * period_ms;
    if (duty_cycle > 0) {
      set_duty_cycle(duty_cycle, timer_num);
    }
    TCCR1B |= (1 << WGM12);  // clear the timer on compare match A
    TIMSK1 |= (1 << OCIE1A); // set interrupt on compare match A
    sei();                   // enable interrupts
    TCCR1B |=
        (1 << CS12) | (1 << CS10); // set prescaler to 1024 and start the timer
    break;
  }
}

void Timer_msec::set_duty_cycle(int duty_cycle, int timer_num) {
  switch (timer_num) {
  default:
    break;
  case 0:
    OCR0B = OCR0A * (float)duty_cycle / 100;
    TIMSK0 |= (1 << OCIE0B); // set interrupt on compare match B
    break;
  case 1:
    OCR1B = OCR1A * (float)duty_cycle / 100;
    TIMSK1 |= (1 << OCIE1B); // set interrupt on compare match B
    break;
  }
}
