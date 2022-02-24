#ifndef HW_JOYSTICK_H_
#define HW_JOYSTICK_H_

#include "Common.h"

typedef uint8_t ButtonStateType;

enum JoystickButton {
  ButtonA = 0,
  ButtonB = 1,
  ButtonStart = 2,
  ButtonSelect = 3,
  ButtonUp = 4,
  ButtonDown = 5,
  ButtonLeft = 6,
  ButtonRight = 7
};

void hwJoystickSetup();

ButtonStateType hwJoystickState();

#endif /* HW_JOYSTICK_H_ */
