#ifndef DRIVERLAYER_H
#define DRIVERLAYER_H

#include "drivers/Display.h"
#include "drivers/Joystick.h"
#include "drivers/NotePlayer.h"
#include "drivers/Timer.h"

extern Display display;
extern Joystick joystick;
extern NotePlayer notePlayer;
extern Timer timer;

class DriverLayer {
public:
  DriverLayer();
  virtual ~DriverLayer();

  void setup();
};

extern DriverLayer driverLayer;

#endif /* DRIVERLAYER_H */
