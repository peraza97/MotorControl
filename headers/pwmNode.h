#ifndef __PWMNODE_H__
#define __PWMNODE_H__

#include "defines.h"

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
