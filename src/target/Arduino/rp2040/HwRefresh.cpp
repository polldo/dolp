#include "hardware/HwConfiguration.h"
#if defined(ARDUINO_NANO_RP2040_CONNECT)

#include "hardware/HwRefresh.h"
#include "Arduino.h"

void hwRefreshSetup()
{
}

void hwRefreshWaitEndFrame()
{
  static const int timeout = FRAME_MSEC;
  static auto time = millis();

  auto waitTime = timeout - int(millis() - time);
#ifdef PROFILING
  Serial.println(waitTime);
#endif
  if (waitTime > 0)
  {
    // arduino delay already exploits mbed thread sleep state
    delay(waitTime);
  }

  time = millis();
}

#endif
