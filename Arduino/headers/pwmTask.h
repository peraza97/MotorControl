#ifndef __PWMTASK_H__
#define __PWMTASK_H__

enum PWMState {PWM_OFF, PWM_RUNNING };

extern double dutyCycle;

int pwmTick(int);

#endif
