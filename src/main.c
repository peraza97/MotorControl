#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <gpiod.h>

#include "pwmNode.h"
#include "defines.h"

int main(int argc, char** argv){
  // variables
  struct PwmNode * leftMotorNode;
  struct gpiod_chip *chip;
  struct gpiod_line * leftMotorInput1, * leftMotorInput2;
  char* period, *dutyCycle;

  // Creeate the gpio lines
  chip = gpiod_chip_open("/dev/gpiochip4");

  if (chip == NULL) {
    printf("chip not found\n");
    return 1;
  }

  leftMotorInput1 = gpiod_chip_get_line(chip, LEFT_MOTOR_INPUT1);  
  gpiod_line_request_output(leftMotorInput1, "example1", 0);
  gpiod_line_set_value(leftMotorInput1, 1);

  leftMotorInput2 = gpiod_chip_get_line(chip, LEFT_MOTOR_INPUT2);  
  gpiod_line_request_output(leftMotorInput2, "example2", 0);
  gpiod_line_set_value(leftMotorInput2, 0);

  // Create the PWN Node
  leftMotorNode = createPwmNode(LEFT_MOTOR_CHIP, LEFT_MOTOR_CHANNEL);
  leftMotorNode->setUp(leftMotorNode);

  // Set the period of the PWM PIN
  leftMotorNode->setPeriod(leftMotorNode, 500000);
  period = leftMotorNode->getPeriod(leftMotorNode);
  printf("period set to %s",period);
  free(period);

  // Set the duty cycle of the PWM PIN
  leftMotorNode->setDutyCycle(leftMotorNode, 250000);
  dutyCycle = leftMotorNode->getDutyCycle(leftMotorNode);
  printf("duty cycle set to %s",dutyCycle);
  free(dutyCycle);

  // ENABLE THE PIN
  leftMotorNode->enable(leftMotorNode);
  usleep(10000 * MICROTOMILLI);

  // Clean up pins
  leftMotorNode->disable(leftMotorNode);  
  leftMotorNode->close(leftMotorNode);

  gpiod_line_set_value(leftMotorInput1, 0);
  gpiod_line_set_value(leftMotorInput2, 0);

  gpiod_line_release(leftMotorInput1);
  gpiod_line_release(leftMotorInput2);
  gpiod_chip_close(chip);  
  return 0;
}
