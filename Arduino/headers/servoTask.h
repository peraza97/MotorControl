#ifndef __SERVOTASK_H__
#define __SERVOTASK_H__

#define SERVO_BOTTOM 1100
#define SERVO_TOP 5100

enum ServoState { SERVO_OFF, SERVO_MOVE , SERVO_DELAY};

extern int servoDegree;

void servoSetUp();
void servoUpdate(int);

int servoTick(int);

#endif
