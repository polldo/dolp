#ifndef TIME_COMPONENT_H
#define TIME_COMPONENT_H

#ifndef TIMEOUTS_FOR_ENTITY
#define TIMEOUTS_FOR_ENTITY (2)
#endif

#include "Common.h"

#include "drivers/DriverLayer.h"

class Entity;

class TimeComponent
{
public:
  TimeComponent() {}
  ~TimeComponent() {}

  void init()
  {
    for (int i = 0; i < TIMEOUTS_FOR_ENTITY; i++)
    {
      _timeouts[i] = 0;
    }
  }

  void deinit()
  {
    for (int i = 0; i < TIMEOUTS_FOR_ENTITY; i++)
    {
      if (_timeouts[i] > 0)
        timer.deleteTimeout(_timeouts[i]);
    }
  }

  TimeoutId init(uint8_t index)
  {
    if (index >= TIMEOUTS_FOR_ENTITY)
    {
      return 0;
    }
    // Don't reallocate already existing timeouts.
    if (!_timeouts[index])
    {
      _timeouts[index] = timer.newTimeout();
    }
    return _timeouts[index];
  }

  void deinit(uint8_t index)
  {
    if (index >= TIMEOUTS_FOR_ENTITY)
    {
      return;
    }
    if (_timeouts[index] > 0)
    {
      timer.deleteTimeout(_timeouts[index]);
      _timeouts[index] = 0;
    }
  }

  TimeoutId getTimeout(uint8_t index)
  {
    if (index >= TIMEOUTS_FOR_ENTITY)
    {
      return 0;
    }
    return _timeouts[index];
  }

private:
  TimeoutId _timeouts[TIMEOUTS_FOR_ENTITY];
};

#endif
