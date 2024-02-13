#ifndef __LED_TASK_H__
#define __LED_TASK_H__

enum LEDState {LED_OFF, LED_ON};

void ledSetUp();

int ledTick(int);

#endif
