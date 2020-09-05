#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include <Common.h>
#include "hardware/HwJoystick.h"

enum JoystickButton {
  ButtonA = 0,
  ButtonB = 1
};

class Joystick {

public:
    Joystick();
    virtual ~Joystick();

    void setup();

    void update();

    bool held(JoystickButton button);

    bool pressed(JoystickButton button);

private:
    ButtonStateType _buttonStateOld;
    ButtonStateType _buttonPressed;
};

#endif /* JOYSTICK_H_ */
