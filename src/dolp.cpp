#include "dolp.h"

void Dolp::setup()
{
    driverLayer.setup();
}

void Dolp::loopBegin()
{
    display.send();
    joystick.update();
}

void Dolp::loopEnd()
{
    timer.waitEndFrame();
}

Dolp dolp;
