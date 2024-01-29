#ifndef __MOTOR_TASK_H__
#define __MOTOR_TASK_H__
#include <gpiod.h> 
#include "pwmNode.h"

enum MOTOR_STATE { OFF, RUNNING };

extern struct PwmNode* leftMotor;
extern struct gpiod_line * leftMotorInput1; 
extern struct gpiod_line * leftMotorInput2; 

int motorTask(int);
void updateMotor(struct PwmNode*, int, int, struct gpiod_line*, int, struct gpiod_line*, int);
#endif
