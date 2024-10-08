#include <avr/interrupt.h>
#include <timer_msec.hpp>

#define CPU_FREQ 16000000

Timer_msec::Timer_msec(float period_ms, int duty_cycle, int timer_num)
    : timer_num(timer_num), period_ms(period_ms), duty_cycle(duty_cycle) {}

void Timer_msec::init() {
  switch (this->timer_num) {
  default:
    break;
  case 0:
    // Set the Timer Mode to CTC
    TCCR0A |= (1 << WGM01);
    // Set the value that you want to count to
    OCR0A = (CPU_FREQ / 256 - 1) / 1000 * this->period_ms;
    TIMSK0 |= (1 << OCIE0A); // Set the ISR COMPA vect
    if (this->duty_cycle > 0) {
      set_duty_cycle(this->duty_cycle);
    }
    sei(); // enable interrupts
    TCCR0B |= (1 << CS02);
    // set prescaler to 256 and start the timer
    break;
  case 1:
    // this code sets up timer1 for a 1s @ 16Mhz Clock (mode 4)
    // counting 16000000/1024 cycles of a clock prescaled by 1024
    TCCR1A = 0; // set timer1 to normal operation (all bits in control registers
                // A and B set to zero)
    TCCR1B = 0;
    TCNT1 = 0; // initialize counter value to 0
    // assign target count to compare register A (must be less than 65536)
    OCR1A = (CPU_FREQ / 1024 - 1) / 1000 * this->period_ms;
    if (this->duty_cycle > 0) {
      set_duty_cycle(this->duty_cycle);
    }
    TCCR1B |= (1 << WGM12);  // clear the timer on compare match A
    TIMSK1 |= (1 << OCIE1A); // set interrupt on compare match A
    sei();                   // enable interrupts
    TCCR1B |=
        (1 << CS12) | (1 << CS10); // set prescaler to 1024 and start the timer
    break;
  case 2:
    OCR2A = (CPU_FREQ / 64 - 1) / 1000 * period_ms;
    if (duty_cycle > 0) {
      set_duty_cycle(this->duty_cycle);
    }

    TCCR2A |= (1 << WGM21);
    // Set to CTC Mode

    TIMSK2 |= (1 << OCIE2A);
    // Set interrupt on compare match

    TCCR2B |= (1 << CS21);
    // set prescaler to 64 and starts PWM

    sei();
    // enable interrupts
  }
}

void Timer_msec::set_duty_cycle(int duty_cycle) {
  this->duty_cycle = duty_cycle;
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
  case 2:
    OCR2B = OCR2A * (float)duty_cycle / 100;
    TIMSK2 |= (1 << OCIE2B); // set interrupt on compare match B
    break;
  }
}
