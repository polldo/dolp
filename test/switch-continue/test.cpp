#include <stdio.h>
#include <iostream>

#include <math.h>

typedef uint8_t TimeoutId;
#define NUM_TIMEOUTS 5

struct Timeout
{
  // Timeout id corresponds to its index in _timeouts array
  // Id 0 is reserved
  uint8_t startTicks;
  uint8_t ticks;
  // bool reset;
  // bool assigned;
  bool repeat;
};

Timeout _timeouts[NUM_TIMEOUTS];

void stopTimeout(TimeoutId id)
{
	if (id >= NUM_TIMEOUTS)
	{
		return;
	}
	auto &tm = _timeouts[id];
	tm.ticks = 0;
	tm.startTicks = 0;
	tm.repeat = false;
}

void setTimeout(TimeoutId id, uint64_t time, bool repeat)
{
	if (id >= NUM_TIMEOUTS)
	{
		return;
	}
	auto &tm = _timeouts[id];
	//tm.startTicks = time / FRAME_MSEC + 1;
	tm.startTicks = time + 1;
	tm.ticks = tm.startTicks;
	tm.repeat = repeat;
}


int main() {
	for (int i = 0; i < NUM_TIMEOUTS; i++)
	{
		stopTimeout(i);
	}

  setTimeout(2, 10, false);
  setTimeout(3, 5, false);
  setTimeout(4, 2, true);

  for (int j = 0; j < 10; j ++) 
  {

    for (int i = 0; i < NUM_TIMEOUTS; i++)
    {
      switch (_timeouts[i].ticks)
      {
      // Timeouts with ticks at 0 are stopped.
      case 0:
        continue;

      // Timeouts with ticks at 1 have just terminated.
      case 1:
        if (_timeouts[i].repeat)
        {
          _timeouts[i].ticks = _timeouts[i].startTicks;
          continue;
        }
        // Stop timeout if repeat is false.
        _timeouts[i].ticks = 0;
        break;

      default:
        _timeouts[i].ticks -= 1;
        continue;
      }
    }

   for (int i = 0; i < NUM_TIMEOUTS; i++)
    {
      std::cout << "index: " << i << "   ticks: " << _timeouts[i].ticks << "\n";
    }
    std::cout << "\n";
  }
}
