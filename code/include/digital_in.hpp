#ifndef DIGITAL_IN_H
#define DIGITAL_IN_H
#include <stdint.h>
class Digital_in {
public:
  Digital_in(int pin_number);

  void init();
  bool is_hi();
  bool is_lo();

private:
  uint8_t pin_mask;
};
#endif // !DIGITAL_IN_H
