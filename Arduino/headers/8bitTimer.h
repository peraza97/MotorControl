#ifndef __8BITTIMER_H__
#define __8BITTIMER_H__

#include <avr/interrupt.h>

volatile unsigned char Timer8BitFlag = 0; // TimerISR() sets this to 1. C programmer should clear to 0.

unsigned long _avr_8bitTimer_Max = 1; 
unsigned long _avr_8bitTimer_cntcurr = 0; 

// Set TimerISR() to tick every M ms
void Timer8BitSet(unsigned long M) {
	_avr_8bitTimer_Max = M;
	_avr_8bitTimer_cntcurr = _avr_8bitTimer_Max;
}

void Timer8BitOn() {
	TCCR0A 	= (1 << WGM01);	// CTC mode (clear timer on compare)

  TCCR0B = (1 << CS02) | (1 << CS00); // Prescaler 1024
                 // clock will have 15625 ticks/s

	// AVR output compare register OCR0A.
	OCR0A 	= 15;	// Timer interrupt will be generated when TCNT1==OCR1A
					// We want a 1 ms tick. 0.001 s * 15,625 ticks/s = 15.625
					// So when TCNT1 register equals 15 1 ms has passed
	TIMSK0	= (1 << OCIE0A); // enables compare match interrupt

	//Initialize avr counter
	TCNT0 = 0;
	_avr_8bitTimer_cntcurr = _avr_8bitTimer_Max;

	//Enable global interrupts
  sei();
}

void Timer8BitOff() {
	TCCR0B 	= 0x00; 
}

void Timer8BitISR() {
	Timer8BitFlag = 1;
}

// In our approach, the C programmer does not touch this ISR, but rather TimerISR()
ISR(TIMER0_COMPA_vect)
{
	// CPU automatically calls when TCNT0 == OCR0 (every 1 ms per TimerOn settings)
	_avr_8bitTimer_cntcurr--; 			// Count down to 0 rather than up to TOP
	if (_avr_8bitTimer_cntcurr == 0) { 	// results in a more efficient compare
		Timer8BitISR(); 				// Call the ISR that the user uses
		_avr_8bitTimer_cntcurr = _avr_8bitTimer_Max;
	}
}

#endif
