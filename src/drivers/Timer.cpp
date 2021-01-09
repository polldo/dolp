#include <drivers/Timer.h>
#include <hardware/HwRefresh.h>

Timer::Timer() :
	_tick(0),
	_secTick(0),
	_seconds(0)
{
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
	if (++_secTick == FPS) {
		_secTick = 0;
		++_seconds;
	}
}
