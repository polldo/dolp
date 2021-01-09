#include <drivers/Timer.h>
#include <hardware/HwRefresh.h>

Timer::Timer() :
	_tick(0),
	_secTick(0),
	_seconds(0)
{
	for (int i = 0; i < NUM_TIMEOUTS; i++) {
		_timeouts[i].assigned = false;
		_timeouts[i].ticks = 0;
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
	if (++_secTick == FPS) {
		_secTick = 0;
		++_seconds;
	}
	// Update timeouts
	updateTimeout();
}

int Timer::newTimeout()
{
	// Timeout 0 is reserved
	for (int i = 1; i < NUM_TIMEOUTS; i++) {
		if (!_timeouts[i].assigned) {
			_timeouts[i].assigned = true;
			return i;
		}
	}
	return -1;
}

void Timer::deleteTimeout(int id)
{
	if (_timeouts[id].assigned) {
		_timeouts[id].assigned = false;
		_timeouts[id].ticks = 0;
	}
}

void Timer::updateTimeout()
{
	for (int i = 1; i < NUM_TIMEOUTS; i++) {
		if (_timeouts[i].assigned && _timeouts[i].ticks > 0) {
			_timeouts[i].ticks -= 1;
		}
	}
}

void Timer::refreshTimeout(int id, uint64_t time)
{
	_timeouts[id].ticks = time / FRAME_MSEC + 1;
}

bool Timer::checkTimeout(int id)
{
	return _timeouts[id].ticks == 1;
}
