#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "pwmNode.h"

struct PwmNode * createPwmNode(int chip, int channel) {
    struct PwmNode *pwm = malloc(sizeof (struct PwmNode));
    pwm->chip = chip;
    pwm->channel = channel;
    
    pwm->chipPath = (char *)malloc(strlen(PWM_CHIP) * sizeof(char));
    sprintf(pwm->chipPath, PWM_CHIP, chip); 

    pwm->channelPath = (char *)malloc(strlen(PWM_NODE) - 1 * sizeof(char));
    sprintf(pwm->channelPath, PWM_NODE, chip, channel); 

    pwm->setUp = &exportPwm;
    pwm->close = &unexportPwm;
    pwm->setPeriod = &setPeriod;
    pwm->getPeriod = &getPeriod;
    pwm->setDutyCycle = &setDutyCycle;
    pwm->getDutyCycle = &getDutyCycle;
    pwm->enable = &enable;
    pwm->disable = &disable;
    
    return pwm;
}

int exportPwm(struct PwmNode * pwmNode) {
    char exportPath[strlen(pwmNode->chipPath) + strlen(PWM_EXPORT) + 1];
    strcpy(exportPath, pwmNode->chipPath);
    strcat(exportPath, PWM_EXPORT);

    FILE * export_fd = fopen(exportPath, "w");

    if (export_fd != NULL) {
        fprintf(export_fd, "%d", pwmNode->channel);
        fclose(export_fd);
    } else {
        perror("Error opening file");
        return -1;
    }
}

int unexportPwm(struct PwmNode * pwmNode) {
    char unexportPath[strlen(pwmNode->chipPath) + strlen(PWM_UNEXPORT) + 1];
    strcpy(unexportPath, pwmNode->chipPath);
    strcat(unexportPath, PWM_UNEXPORT);

    FILE * unexport_fd = fopen(unexportPath, "w");

    if (unexport_fd != NULL) {
        fprintf(unexport_fd, "%d", pwmNode->channel);
        fclose(unexport_fd);
    } else {
        perror("Error opening file");
        return -1;
    }
}

int setPeriod(struct PwmNode * pwmNode, int period) {
    char periodPath[strlen(pwmNode->channelPath) + strlen(PWM_PERIOD) + 1];
    strcpy(periodPath, pwmNode->channelPath);
    strcat(periodPath, PWM_PERIOD);

    FILE * period_fd = fopen(periodPath, "w");

    if (period_fd != NULL) {
        fprintf(period_fd, "%d", period);
        fclose(period_fd);
    } else {
        perror("Error opening file");
        return -1;
    }
}

char * getPeriod(struct PwmNode * pwmNode) {
    char periodPath[strlen(pwmNode->channelPath) + strlen(PWM_PERIOD) + 1];
    strcpy(periodPath, pwmNode->channelPath);
    strcat(periodPath, PWM_PERIOD);

    FILE * period_fd = fopen(periodPath, "r");

    fseek(period_fd, 0, SEEK_END);
    long fileSize = ftell(period_fd);
    fseek(period_fd, 0, SEEK_SET);

    char *buffer = (char *)malloc(fileSize + 1); // +1 for null terminator
    if (buffer == NULL) {
        perror("Memory allocation error");
        fclose(period_fd);
        return NULL;
    }

    fread(buffer, 1, fileSize, period_fd);
    buffer[fileSize] = '\0'; // Null-terminate the string

    fclose(period_fd);
    return buffer;
}

int setDutyCycle(struct PwmNode * pwmNode, int dutyCycle) {
    char dutyCyclePath[strlen(pwmNode->channelPath) + strlen(PWM_DUTY_CYCLE) + 1];
    strcpy(dutyCyclePath, pwmNode->channelPath);
    strcat(dutyCyclePath, PWM_DUTY_CYCLE);

    FILE * dutyCycle_fd = fopen(dutyCyclePath, "w");
    if (dutyCycle_fd != NULL) {
        fprintf(dutyCycle_fd, "%d", dutyCycle);
        fclose(dutyCycle_fd);
    } else {
        perror("Error opening file");
        return -1;
    }
}

char * getDutyCycle(struct PwmNode * pwmNode) {
    char dutyCyclePath[strlen(pwmNode->channelPath) + strlen(PWM_DUTY_CYCLE) + 1];
    strcpy(dutyCyclePath, pwmNode->channelPath);
    strcat(dutyCyclePath, PWM_DUTY_CYCLE);

    FILE * dutyCycle_fd = fopen(dutyCyclePath, "r");

    fseek(dutyCycle_fd, 0, SEEK_END);
    long fileSize = ftell(dutyCycle_fd);
    fseek(dutyCycle_fd, 0, SEEK_SET);

    char *buffer = (char *)malloc(fileSize + 1); // +1 for null terminator
    if (buffer == NULL) {
        perror("Memory allocation error");
        fclose(dutyCycle_fd);
        return NULL;
    }

    fread(buffer, 1, fileSize, dutyCycle_fd);
    buffer[fileSize] = '\0'; // Null-terminate the string

    fclose(dutyCycle_fd);
    return buffer;
}

int enable(struct PwmNode *pwmNode) {
    char enablePath[strlen(pwmNode->channelPath) + strlen(PWM_ENABLE) + 1];
    strcpy(enablePath, pwmNode->channelPath);
    strcat(enablePath, PWM_ENABLE);

    FILE * enable_fd = fopen(enablePath, "w");

    if (enable_fd != NULL) {
        fprintf(enable_fd, "%d", 1);
        fclose(enable_fd);
    } else {
        perror("Error opening file");
        return -1;
    }
}

int disable(struct PwmNode *pwmNode) {
    char enablePath[strlen(pwmNode->channelPath) + strlen(PWM_ENABLE) + 1];
    strcpy(enablePath, pwmNode->channelPath);
    strcat(enablePath, PWM_ENABLE);

    FILE * enable_fd = fopen(enablePath, "w");

    if (enable_fd != NULL) {
        fprintf(enable_fd, "%d", 0);
        fclose(enable_fd);
    } else {
        perror("Error opening file");
        return -1;
    }
}