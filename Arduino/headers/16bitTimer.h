////////////////////////////////////////////////////////////////////////////////
// Permission to copy is granted provided that this header remains intact. 
// This software is provided with no warranties.
////////////////////////////////////////////////////////////////////////////////

#ifndef __16BITTIMER_H__
#define __16BITTIMER_H__

#include <avr/interrupt.h>

volatile unsigned char Timer16BitFlag = 0; // TimerISR() sets this to 1. C programmer should clear to 0.

// Internal variables for mapping AVR's ISR to our cleaner TimerISR model.
unsigned long _avr_16bitTimer_M = 1; // Start count from here, down to 0. Default 1ms
unsigned long _avr_16bitTimer_cntcurr = 0; // Current internal count of 1ms ticks

// Set TimerISR() to tick every M ms
void Timer16BitSet(unsigned long M) {
	_avr_16bitTimer_M = M;
	_avr_16bitTimer_cntcurr = _avr_16bitTimer_M;
}

void Timer16BitOn() {
	// AVR timer/counter controller register TCCR1
	TCCR1B 	= 0x0B;	// bit3 = 1: CTC mode (clear timer on compare)
					// bit2bit1bit0=011: prescaler /64
					// 00001011: 0x0B
					// SO, 16 MHz clock or 16,000,000 /64 = 250,000 ticks/s
					// Thus, TCNT1 register will count at 250,000 ticks/s

	// AVR output compare register OCR1A.
	OCR1A 	= 250;	// Timer interrupt will be generated when TCNT1==OCR1A
					// We want a 1 ms tick. 0.001 s * 250,000 ticks/s = 250
					// So when TCNT1 register equals 250,
					// 1 ms has passed. Thus, we compare to 250.
					// AVR timer interrupt mask register

	TIMSK1 	= 0x02; // bit1: OCIE1A -- enables compare match interrupt

	//Initialize avr counter
	TCNT1 = 0;

	// TimerISR will be called every _avr_timer_cntcurr milliseconds
	_avr_16bitTimer_cntcurr = _avr_16bitTimer_M;

	//Enable global interrupts
	SREG |= 0x80;	// 0x80: 1000000
}

void Timer16BitOff() {
	TCCR1B 	= 0x00; // bit3bit2bit1bit0=0000: timer off
}

void Timer16BitISR() {
	Timer16BitFlag = 1;
}

// In our approach, the C programmer does not touch this ISR, but rather TimerISR()
ISR(TIMER1_COMPA_vect)
{
	// CPU automatically calls when TCNT0 == OCR0 (every 1 ms per TimerOn settings)
	_avr_16bitTimer_cntcurr--; 			// Count down to 0 rather than up to TOP
	if (_avr_16bitTimer_cntcurr == 0) { 	// results in a more efficient compare
		Timer16BitISR(); 				// Call the ISR that the user uses
		_avr_16bitTimer_cntcurr = _avr_16bitTimer_M;
	}
}

#endif
