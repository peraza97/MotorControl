#include "motorTask.h"

int motorTask(int state)
{
  return state;
}


void updateMotor(struct PwmNode* motorNode, int period, int dutyCycle, struct gpiod_line* inputLine1,  int inputValue1, struct gpiod_line* inputLine2, int inputValue2) {
  motorNode->setPeriod(motorNode, period);
  motorNode->setDutyCycle(motorNode, dutyCycle);

  if (inputLine1 != NULL) {
    gpiod_line_set_value(inputLine1, inputValue1);
  }
  if (inputLine2 != NULL) {
    gpiod_line_set_value(inputLine2, inputValue2);
  }
}
