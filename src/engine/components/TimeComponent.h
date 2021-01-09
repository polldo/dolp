#ifndef TIME_COMPONENT_H
#define TIME_COMPONENT_H

#ifndef TIMEOUTS_FOR_ENTITY
#define TIMEOUTS_FOR_ENTITY (2)
#endif

#include "Common.h"

#include "drivers/DriverLayer.h"

class Entity;

class TimeComponent {
  public:
    TimeComponent() {}
    ~TimeComponent() {}

    // TODO: Check whether passed indexes are < TIMEOUTS_FOR_ENTITY 
    // (i.e. from 0 to TIMEOUTS_FOR_ENTITY)

    void init() 
    {
      for (int i = 0; i < TIMEOUTS_FOR_ENTITY; i++) {
        _timeouts[i] = 0;
      }
    }

    void init(uint8_t index, uint64_t time) 
    { 
      if (!_timeouts[index]) 
        _timeouts[index] = timer.newTimeout(time); 
      else 
        timer.setTimeout(_timeouts[index], time);
    }

    void deinit() 
    { 
      for (int i = 0; i < TIMEOUTS_FOR_ENTITY; i++) {
        if (_timeouts[i] > 0) timer.deleteTimeout(_timeouts[i]);
      }
    }

    void deinit(uint8_t index) 
    { 
      if (_timeouts[index] > 0) timer.deleteTimeout(_timeouts[index]);
    }

    bool checkTimeout(uint8_t index)
    {
      if (_timeouts[index] > 0) {
        return timer.checkTimeout(_timeouts[index]);
      }
      return false;
    }

    TimeoutId getTimeout(uint8_t index)
    {
      return _timeouts[index];
    }

  private:
    TimeoutId _timeouts[TIMEOUTS_FOR_ENTITY];
};


#endif 
