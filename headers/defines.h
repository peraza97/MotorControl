#ifndef __DEFINES_H__
#define __DEFINES _H__

// DEFINITIONS
#define PWM_CHIP "/sys/class/pwm/pwmchip%d/"
#define PWM_NODE "/sys/class/pwm/pwmchip%d/pwm%d/"
#define PWM_EXPORT "export"
#define PWM_UNEXPORT "unexport"
#define PWM_ENABLE "enable"
#define PWM_PERIOD "period"
#define PWM_DUTY_CYCLE "duty_cycle"

#define MICROTOMILLI 1000 
#define NANOTOMILLI  1000000


// LEFT MOTOR
#define LEFT_MOTOR_CHIP 2
#define LEFT_MOTOR_CHANNEL 2
#define LEFT_MOTOR 18
#define LEFT_MOTOR_INPUT1 25
#define LEFT_MOTOR_INPUT2 8

#endif
