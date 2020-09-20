#include "drivers/DriverLayer.h"

Display display;
Joystick joystick;
NotePlayer notePlayer;
Timer timer;

void DriverLayer::setup()
{
    display.setup();
    joystick.setup();
    notePlayer.setup();
    timer.setup();
}

DriverLayer driverLayer;
