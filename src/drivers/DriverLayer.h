#ifndef DRIVERLAYER_H
#define DRIVERLAYER_H

#include "drivers/Display.h"
#include "Joystick.h"
#include "NotePlayer.h"
#include "Timer.h"

extern Display display;
extern Joystick joystick;
extern NotePlayer notePlayer;
extern Timer timer;

class DriverLayer {
public:
    DriverLayer() {}
    virtual ~DriverLayer() {}

    void setup();
};

extern DriverLayer driverLayer;

#endif /* DRIVERLAYER_H */
