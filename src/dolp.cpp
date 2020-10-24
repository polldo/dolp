#include "dolp.h"

void Dolp::setup()
{
    driverLayer.setup();
    engine.setup();
}

void Dolp::loopBegin()
{
    display.send();
    joystick.update();

    engine.loop();
}

void Dolp::loopEnd()
{
    timer.waitEndFrame();
}

Dolp dolp;
