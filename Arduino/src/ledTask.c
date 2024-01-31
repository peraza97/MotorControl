#include <gpiod.h>
#include "ledTask.h"

// State machine to control LED A
int ledATick(int state) {
  switch (state) {
    case LED_OFF:
      state = LED_ON;
      gpiod_line_set_value(ledLine, 1);
      break;
    case LED_ON:
      state = LED_OFF;
      gpiod_line_set_value(ledLine, 0);
      break;
    default:
      break;
  }
  return state;
}
