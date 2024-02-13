#include <avr/io.h>

#include "pwmTask.h"

void pwmSetUp() {
  DDRD = (1 << DDD6) | (1 << DDD5);
  TCCR0A = (1 << COM0A1) | (1 << WGM00) | (1 << WGM01); // MODE
  
  TIMSK0 = (1 << TOIE0); // OVERFLOW INTERRUPT 

  OCR0A = (dutyCycle/100.0) * 255; // COUNTER FOR TICKS 

  TCCR0B = (1 << CS02); // PRESCALER of 256
}

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
