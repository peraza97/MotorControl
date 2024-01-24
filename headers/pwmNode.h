#ifndef __PWMNODE_H__
#define __PWMNODE_H__

#define PWM_CHIP "/sys/class/pwm/pwmchip%d/"
#define PWM_NODE "/sys/class/pwm/pwmchip%d/pwm%d/"
#define PWM_EXPORT "export"
#define PWM_UNEXPORT "unexport"
#define PWM_ENABLE "enable"
#define PWM_PERIOD "period"
#define PWM_DUTY_CYCLE "duty_cycle"

struct PwmNode {
    int chip;
    int channel;
    char* chipPath;
    char* channelPath;

    int (*setUp)(struct PwmNode * pwmNode);
    int (*close)(struct PwmNode * pwmNode);
    int (*setPeriod)(struct PwmNode * pwmNode, int period);
    char* (*getPeriod)(struct PwmNode * pwmNode);
    int (*setDutyCycle)(struct PwmNode * pwmNode, int dutyCycle);
    char* (*getDutyCycle)(struct PwmNode * pwmNode);
    int (*enable)(struct PwmNode *pwmNode);
    int (*disable)(struct PwmNode *pwmNode);
};

struct PwmNode* createPwmNode(int chip, int channel);
int exportPwm(struct PwmNode * pwmNode);
int unexportPwm(struct PwmNode * pwmNode);
int setPeriod(struct PwmNode * pwmNode, int period);
char* getPeriod(struct PwmNode * pwmNode);
int setDutyCycle(struct PwmNode * pwmNode, int dutyCycle);
char* getDutyCycle(struct PwmNode * pwmNode);
int enable(struct PwmNode *pwmNode);
int disable(struct PwmNode *pwmNode);

#endif