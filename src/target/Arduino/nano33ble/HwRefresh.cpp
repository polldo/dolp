#include "hardware/HwConfiguration.h"
#if defined (ARDUINO_NANO33BLE)

#include "hardware/HwRefresh.h"
#include "Arduino.h"

void hwRefreshSetup()
{
}

void hwRefreshWaitEndFrame()
{
  static const unsigned long timeout = 33; 
  static auto time = millis();

  // arduino delay exploits mbed thread sleep state
  auto waitTime = timeout - (millis() - time);
#ifdef PROFILING
  Serial.println(waitTime);
#endif
  if (waitTime > 0)
    delay(waitTime);

  time = millis();
}

#endif
