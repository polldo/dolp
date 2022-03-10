#include <drivers/Timer.h>
#include <hardware/HwRefresh.h>

Timer::Timer() : _tick(0),
				 _secTick(0),
				 _seconds(0)
{
	for (int i = 0; i < NUM_TIMEOUTS; i++)
	{
		deleteTimeout(i);
	}
}

Timer::~Timer()
{
}

void Timer::setup()
{
	hwRefreshSetup();
}

uint64_t Timer::getMilliseconds()
{
	return _milliseconds;
}

uint64_t Timer::getSeconds()
{
	return _seconds;
}

void Timer::waitEndFrame()
{
	hwRefreshWaitEndFrame();

	// Update ticks and time counters
	++_tick;
	_milliseconds += FRAME_MSEC;
	if (++_secTick == FPS)
	{
		_secTick = 0;
		++_seconds;
	}
	// Update timeouts
	updateTimeout();
}

TimeoutId Timer::newTimeout()
{
	// Reserve 0 for errors during timeout construction.
	for (int i = 1; i < NUM_TIMEOUTS; i++)
	{
		if (!_timeouts[i].assigned)
		{
			_timeouts[i].assigned = true;
			return i;
		}
	}
	return 0;
}

void Timer::deleteTimeout(TimeoutId id)
{
	if (id >= NUM_TIMEOUTS)
	{
		return;
	}
	auto &tm = _timeouts[id];
	tm.ticks = 0;
	tm.startTicks = 0;
	tm.assigned = false;
	tm.ticked = false;
}

void Timer::setTimeout(TimeoutId id, uint64_t time, bool repeat)
{
	if (id >= NUM_TIMEOUTS)
	{
		return;
	}
	auto &tm = _timeouts[id];
	if (!tm.assigned)
	{
		return;
	}
	tm.startTicks = time / FRAME_MSEC + 1;
	tm.ticks = tm.startTicks;
	tm.repeat = repeat;
	tm.ticked = false;
}

bool Timer::checkTimeout(TimeoutId id)
{
	if (id >= NUM_TIMEOUTS)
	{
		return false;
	}
	if (_timeouts[id].ticked)
	{
		_timeouts[id].ticked = false;
		return true;
	}
	return false;
}

void Timer::updateTimeout()
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
			_timeouts[i].ticked = true;
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
}
