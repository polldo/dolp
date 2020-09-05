#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include <Common.h>

#define BUTTON_A 0
#define BUTTON_B 1

class Joystick {

public:
    Joystick();
    virtual ~Joystick();

    void setup();

    void update();

    uint8_t held(uint8_t button);

    uint8_t pressed(uint8_t button);

private:
    uint8_t _buttonStateOld;
    uint8_t _buttonPressed;
}

#endif /* JOYSTICK_H_ */
