#ifndef REFRESH_H_
#define REFRESH_H_

#include <Common.h>

class Timer {
public:
  Timer();
  virtual ~Timer();

  void setup();
  void waitEndFrame();

  uint64_t getMilliseconds();
  uint64_t getSeconds();

private:
  unsigned long long _tick;
  uint8_t _secTick;
  uint64_t _seconds;
  uint64_t _milliseconds;
};

#endif /* REFRESH_H_ */
