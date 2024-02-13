#ifndef __PWMTASK_H__
#define __PWMTASK_H__

enum PWMState {PWM_OFF, PWM_RUNNING };

extern double dutyCycle;

void pwmSetUp();
int pwmTick(int);

#endif
