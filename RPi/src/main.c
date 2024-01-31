#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <gpiod.h>
#include <signal.h>

#include "pwmNode.h"
#include "defines.h"
#include "motorTask.h"

//GLOBAL VARS
struct PwmNode * leftMotor = NULL;
struct gpiod_chip *chip;
struct gpiod_line * leftMotorInput1, * leftMotorInput2;

void setUp() {
  chip = gpiod_chip_open("/dev/gpiochip4");

  if (chip == NULL) {
    printf("chip not found\n");
    exit(1);
  }

  // SET UP LEFT MOTOR INPUT PINS
  leftMotorInput1 = gpiod_chip_get_line(chip, LEFT_MOTOR_INPUT1);  
  gpiod_line_request_output(leftMotorInput1, "example1", 0);
  leftMotorInput2 = gpiod_chip_get_line(chip, LEFT_MOTOR_INPUT2);  
  gpiod_line_request_output(leftMotorInput2, "example2", 0);
  leftMotor = createPwmNode(LEFT_MOTOR_CHIP, LEFT_MOTOR_CHANNEL);
  leftMotor->setUp(leftMotor);
  updateMotor(leftMotor, 0, 0, leftMotorInput1, 1, leftMotorInput2, 0); 
  leftMotor->enable(leftMotor);
}

void cleanUp() {
  // CLEAN UP LEFT MOTOR PINS
  leftMotor->disable(leftMotor);  
  leftMotor->close(leftMotor);

  gpiod_line_set_value(leftMotorInput1, 0);
  gpiod_line_set_value(leftMotorInput2, 0);

  gpiod_line_release(leftMotorInput1);
  gpiod_line_release(leftMotorInput2);
  gpiod_chip_close(chip); 
}

void handleCtrlC(int signum) {
  printf("\nCtrl+C pressed. cleaning up...\n");
  cleanUp();
  printf("exiting\n");
  exit(signum);
}

int main(int argc, char** argv){
  signal(SIGINT, handleCtrlC);
  setUp();

  updateMotor(leftMotor, 500000, 200000, NULL, 0, NULL, 0);
  usleep(5000 * MICROTOMILLI);
  updateMotor(leftMotor, 500000, 350000, NULL, 0, NULL, 0);
  usleep(5000 * MICROTOMILLI);

  cleanUp();
  return 0;
}
