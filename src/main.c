#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <gpiod.h>

#include "pwmNode.h"

#define MICROTOMILLI 1000 
#define NANOTOMILLI  1000000

int main(int argc, char** argv){
  // variables
  struct PwmNode * node;
  struct gpiod_chip *chip;
  struct gpiod_line * input1Line, * input2Line;
  char* period, *dutyCycle;

  // Creeate the gpio lines
  chip = gpiod_chip_open("/dev/gpiochip4");

  if (chip == NULL) {
    printf("chip not found\n");
    return 1;
  }

  input1Line = gpiod_chip_get_line(chip, 25);  
  gpiod_line_request_output(input1Line, "example1", 0);
  gpiod_line_set_value(input1Line, 1);

  input2Line = gpiod_chip_get_line(chip, 8);  
  gpiod_line_request_output(input2Line, "example2", 0);
  gpiod_line_set_value(input2Line, 0);

  // Create the PWN Node
  node = createPwmNode(2, 2);
  node->setUp(node);

  // Set the period of the PWM PIN
  node->setPeriod(node, 500000);
  period = node->getPeriod(node);
  printf("period set to %s",period);
  free(period);

  // Set the duty cycle of the PWM PIN
  node->setDutyCycle(node, 250000);
  dutyCycle = node->getDutyCycle(node);
  printf("duty cycle set to %s",dutyCycle);
  free(dutyCycle);

  // ENABLE THE PIN
  node->enable(node);
  usleep(10000 * MICROTOMILLI);

  // Clean up pins
  node->disable(node);  
  node->close(node);

  gpiod_line_set_value(input1Line, 0);
  gpiod_line_set_value(input2Line, 0);

  gpiod_line_release(input1Line);
  gpiod_line_release(input2Line);
  gpiod_chip_close(chip);  
  return 0;
}
