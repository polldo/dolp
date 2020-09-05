#ifndef HW_JOYSTICK_H_
#define HW_JOYSTICK_H_

#include "Common.h"

typedef uint8_t ButtonStateType;

void hwJoystickSetup();

ButtonStateType hwJoystickState();

#endif /* HW_JOYSTICK_H_ */
