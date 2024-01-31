#include "pwmTask.h"

int pwmTick(int state) {
  switch (state) {
    case PWM_OFF:
    case PWM_RUNNING:
      state = PWM_RUNNING;
      break;
    default:
      state = PWM_OFF;
      break;
  }

  switch (state) {
    case PWM_RUNNING:
      dutyCycle += 10;
      if (dutyCycle > 100 ) {
        dutyCycle = 0;
      };
      break;
  }

  return state;
}
