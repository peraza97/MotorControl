#include <avr/io.h>

#include "servoTask.h"

extern int servoDegree;

// SETUP OCR1A TIMER ON PIN B1
void servoSetUp() {
  DDRB |= (1 << DDB1);
  TCCR1A = (1 << COM1A1) | (1 << WGM11); // COM1A1 WGM11: CLEAR ON COMPARE, SET ON BOTTOM
  TCCR1B =  (1 << WGM13) | (1 << WGM12) | ( 1 << CS11); // PRESCALER OF 8
  ICR1 = 39999; // 40,000 ticks gives us the 50 Hz
  OCR1A = SERVO_BOTTOM;
  
}

void servoUpdate(int value) {
  if (value < SERVO_BOTTOM) {
    OCR1A = SERVO_BOTTOM;
  }
  else if (value > SERVO_TOP) {
    OCR1A = SERVO_TOP;
  }
  else {
    OCR1A = value;
  }
}

int servoTick(int state) {
  static int i;
  static int direction;
  switch(state) {
    case SERVO_OFF:
      i = 0;
      direction = 1;
      state = SERVO_MOVE;
      break;
    case SERVO_MOVE:
      i = 0;
      if (direction) {
        servoDegree += 200;
        if (servoDegree >= SERVO_TOP) {
          direction = 0;
        }
      }
      else {
        servoDegree -= 200;
        if (servoDegree <= SERVO_BOTTOM) {
          direction = 1;
        }
      }
      state = SERVO_DELAY;
      servoUpdate(servoDegree);
      break;
    case SERVO_DELAY:
      if (i++ > 2) {
        state = SERVO_MOVE;
      }
      break;
    default:
      state = SERVO_OFF;
      break;
  }

  return state;
}
