#include <Arduino.h>
#include <context.hpp>
#include <init_state.hpp>
#include <stdlib.h>
//
// Transition macros
#define RESET 'r'
#define SET_PRE_OP 'p'
#define SET_OP 'o'

Context *context;
int command = 0;

int main() {
  init();
  Serial.begin(9600); // Open serial port with baud rate 9600
  Serial.flush();
  context = new Context(new Init_state);

  while (1) {
    if (Serial.available() > 0) {
      command = Serial.read();

      switch (command) {
      case RESET:
        context->reset();
        break;
      case SET_PRE_OP:
        context->set_pre_op();
        break;
      case SET_OP:
        context->set_op();
        break;
      }
    }
    delete context;
  }
}
