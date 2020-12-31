#ifndef HW_JOYSTICK_H_
#define HW_JOYSTICK_H_

#include "Common.h"

typedef uint8_t ButtonStateType;

enum JoystickButton {
  ButtonA = 0,
  ButtonB = 1,
  ButtonC = 2,
  ButtonD = 3,
  ButtonE = 4,
  ButtonF = 5,
  ButtonG = 6,
  ButtonH = 7
};

void hwJoystickSetup();

ButtonStateType hwJoystickState();

#endif /* HW_JOYSTICK_H_ */
