#ifndef DIGITAL_OUT_H
#define DIGITAL_OUT_H
#include <stdint.h>

class Digital_out {
public:
  Digital_out(int pin_number);

  void init();
  void set_hi();
  void set_lo();
  void toggle();

private:
  uint8_t pinMask;
};
#endif // !DIGITAL_OUT_H
