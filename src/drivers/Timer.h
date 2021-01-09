#ifndef REFRESH_H_
#define REFRESH_H_

#include <Common.h>
#include <engine/Pool.h>

#ifndef NUM_TIMEOUTS
#define NUM_TIMEOUTS 100
#endif

struct Timeout {
  //int id;
  bool assigned;
  //bool expired;
  //uint64_t time;
  uint8_t ticks;
};

class Timer {
public:
  Timer();
  virtual ~Timer();

  void setup();
  void waitEndFrame();

  uint64_t getMilliseconds();
  uint64_t getSeconds();

  int newTimeout();
  void deleteTimeout(int id);
  void updateTimeout();
  void refreshTimeout(int id, uint64_t time);
  bool checkTimeout(int id);

private:
  unsigned long long _tick;
  uint8_t _secTick;
  uint64_t _seconds;
  uint64_t _milliseconds;

  Timeout _timeouts[NUM_TIMEOUTS];
  //int timeouts[NUM_TIMEOUTS];
  //bool timeouts
};

#endif /* REFRESH_H_ */
