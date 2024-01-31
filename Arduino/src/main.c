#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "defines.h"
#include "SMTask.h"
#include "ledTask.h"

double dutyCycle = 50;

ISR(TIMER0_OVF_vect) {
  OCR0A = (dutyCycle/100) * 255; 
}

void setUpLed() {
   // ONBOARD LED B5
  DDRB |= (1 << DDB5);
}

void setUpPWMLed() {
  DDRD |= (1 << DDD6);
  TCCR0A |= (1 << COM0A1) | (1 << WGM00) | (1 << WGM01); // MODE
  TIMSK0 |= (1 << TOIE0); // OVERFLOW  

  OCR0A = (dutyCycle/100) * 255; 
  sei();

  TCCR0B |= (1 << CS00) | (1 << CS01); // PRESCALER
}

void setUp() {
  setUpLed();
  setUpPWMLed();
}

int main(void) {
  struct SMTask ledTask;
  ledTask.state = 0;
  ledTask.period = 1000;
  ledTask.elapsedTime = 0;
  ledTask.TickFct = &ledTick;

  struct SMTask tasks[] = { ledTask };
  
  int gcd = findGCD(ledTask.period, 1);
  int numTasks = sizeof(tasks) / sizeof(struct SMTask);
  
  setUp();
  
  while(1) {
    for(int i = 0; i < numTasks; ++i) {
      if (tasks[i].elapsedTime > tasks[i].period) {
        tasks[i].state = tasks[i].TickFct(tasks[i].state);
        tasks[i].elapsedTime = 0;
      }
      tasks[i].elapsedTime += gcd;
    }

    dutyCycle += 5;
    dutyCycle = dutyCycle > 100 ? 0 : dutyCycle;

    _delay_ms(gcd);
  }

  return 0;
}
