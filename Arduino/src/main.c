#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "defines.h"
#include "ledTask.h"
#include "pwmTask.h"
#include "task.h"
#include "timer.h"

double dutyCycle = 50;

void setUpLed() {
   // ONBOARD LED B5
  DDRB = (1 << DDB5);
}

void setUpPWMLed() {
  DDRD = (1 << DDD6);
  TCCR0A = (1 << COM0A1) | (1 << WGM00) | (1 << WGM01); // MODE
  TIMSK0 = (1 << TOIE0); // OVERFLOW INTERRUPT 

  OCR0A = (dutyCycle/100.0) * 255; // COUNTER FOR TICKS 

  TCCR0B = (1 << CS01); // PRESCALER
}

void setUp() {
  setUpLed();
  setUpPWMLed();
}

int main(void) {
  struct SMTask ledTask;
  ledTask.state = 0;
  ledTask.period = 1000;
  ledTask.elapsedTime = 1000;
  ledTask.TickFct = &ledTick;

  struct SMTask pwmTask;
  pwmTask.state = 0;
  pwmTask.period = 500;
  pwmTask.elapsedTime = 500;
  pwmTask.TickFct = &pwmTick;

  struct SMTask tasks[2] = { ledTask, pwmTask };
  
  int numTasks = sizeof(tasks) / sizeof(struct SMTask);
  
  setUp();
  
  TimerSet(PERIOD);
  TimerOn();
  
  while(1) {
    for(int i = 0; i < numTasks; ++i) {
      if (tasks[i].elapsedTime >= tasks[i].period) {
        tasks[i].state = tasks[i].TickFct(tasks[i].state);
        tasks[i].elapsedTime = 0;
      }
      tasks[i].elapsedTime += PERIOD;
    }

    while(!TimerFlag);
    TimerFlag=0;
  }

  return 0;
}

ISR(TIMER0_OVF_vect) {
  OCR0A = (dutyCycle/100.0) * 255; 
}

