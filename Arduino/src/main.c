#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "ledTask.h"
#include "pwmTask.h"
#include "servoTask.h"
#include "task.h"
#include "usart.h"
#include "8bitTimer.h"

#define PERIOD 500

// GLOBAL VARIABLES
double dutyCycle = 50;
int servoDegree = SERVO_BOTTOM;

void clearPorts() {
  DDRB = 0;
  PORTB = 0;
}

void setUp() {
  clearPorts();
  ledSetUp();
  servoSetUp();
}

void debugging() {
  clearPorts();
  USARTSetup();
  ledSetUp();
  servoSetUp();
  
  Timer8BitSet(PERIOD);
  Timer8BitOn();

  int direction = 1;
  int ledState = 1;
  
  while(1) {
    ledState = !ledState;

    char servo[6];
    sprintf(servo, "%d\n", servoDegree);
    USARTWriteString(servo);

    if (ledState) {
      PORTB |= (1 << PORTB5);
    }
    else {
      PORTB &= ~(1 << PORTB5);
    }

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
    servoUpdate(servoDegree);

    while(!Timer8BitFlag){}
    Timer8BitFlag=0;
  }

}

int main(void) {
  debugging();
  return 1;

  struct SMTask ledTask;
  ledTask.state = 0;
  ledTask.period = 1000;
  ledTask.elapsedTime = 1000;
  ledTask.TickFct = &ledTick;

  struct SMTask servoTask;
  servoTask.state = 0;
  servoTask.period = 100;
  servoTask.elapsedTime = 100;
  servoTask.TickFct = &servoTick;

  struct SMTask tasks[] = { ledTask, servoTask };
  
  int numTasks = sizeof(tasks) / sizeof(struct SMTask);

  setUp();
  Timer8BitSet(PERIOD);
  Timer8BitOn();

  while(1) {

    for(int i = 0; i < numTasks; ++i) {
      if (tasks[i].elapsedTime >= tasks[i].period) {
        tasks[i].state = tasks[i].TickFct(tasks[i].state);
        tasks[i].elapsedTime = 0;
      }
      tasks[i].elapsedTime += PERIOD;
    }

    while(!Timer8BitFlag);
    Timer8BitFlag=0;
  }

  return 0;
}
