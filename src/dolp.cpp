#include "dolp.h"

void Dolp::setup()
{
    driverLayer.setup();
    engine.setup();
}

void Dolp::loopBegin()
{
    joystick.update();
    engine.loopBegin();
}

void Dolp::loopEnd()
{
    engine.loopEnd();
    display.send();
    timer.waitEndFrame();
}

Dolp dolp;
