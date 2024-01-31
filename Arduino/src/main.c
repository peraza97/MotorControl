#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "defines.h"

double dutyCycle = 50;

ISR(TIMER0_OVF_vect) {
  OCR0A = (dutyCycle/100) * 255; 
}

unsigned long findGCD(unsigned long int a, unsigned long int b)
{
	unsigned long int c;
	while(1){
		c = a % b;
		if( c == 0 ) { return b; }
		a = b;
		b = c;
	}
	return 0;
}

int main(void) {
  //B5 ONBOARD LED
  DDRB |= (1 << DDB5);

  // PWM PIN
  DDRD |= (1 << DDD6);
  TCCR0A |= (1 << COM0A1) | (1 << WGM00) | (1 << WGM01); // MODE
  TIMSK0 |= (1 << TOIE0); // OVERFLOW  

  OCR0A = (dutyCycle/100) * 255; 
  sei();

  TCCR0B |= (1 << CS00) | (1 << CS01); // PRESCALER

  while(1) {
    PORTB = PORTB | (1 << PORTB5);
    _delay_ms(1000);
    PORTB = PORTB & ~(1 << PORTB5);
    _delay_ms(1000);

    dutyCycle += 10;
    dutyCycle = dutyCycle > 100 ? 0 : dutyCycle;
  }

  return 0;
}
