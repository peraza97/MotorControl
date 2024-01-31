#include <avr/io.h>

#include "ledTask.h"

// State machine to control LED A
int ledTick(int state) {
  switch (state) {
    case LED_OFF:
      state = LED_ON;
      PORTB = (1 << PORTB5);
      break;
    case LED_ON:
      state = LED_OFF;
      PORTB = ~(1 << PORTB5);
      break;
    default:
      break;
  }

  return state;
}
