#ifndef REFRESH_H_
#define REFRESH_H_

#include <Common.h>

#ifndef NUM_TIMEOUTS
#define NUM_TIMEOUTS 200
#endif

struct Timeout
{
  uint8_t startTicks;
  uint8_t ticks;
  bool assigned;
  bool repeat;
  bool ticked;
};

// TimeoutId corresponds to its index in _timeouts array
typedef uint8_t TimeoutId;

class Timer
{
public:
  Timer();
  virtual ~Timer();

  void setup();
  void waitEndFrame();

  uint64_t getMilliseconds();
  uint64_t getSeconds();

  TimeoutId newTimeout();
  void deleteTimeout(TimeoutId id);
  void setTimeout(TimeoutId id, uint64_t time, bool repeat);
  bool checkTimeout(TimeoutId id);

private:
  unsigned long long _tick;
  uint8_t _secTick;
  uint64_t _seconds;
  uint64_t _milliseconds;

  void updateTimeout();

  Timeout _timeouts[NUM_TIMEOUTS];
};

#endif /* REFRESH_H_ */
