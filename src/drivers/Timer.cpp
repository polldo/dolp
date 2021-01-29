#include <drivers/Timer.h>
#include <hardware/HwRefresh.h>

Timer::Timer() :
	_tick(0),
	_secTick(0),
	_seconds(0)
{
	for (int i = 0; i < NUM_TIMEOUTS; i++) {
		_timeouts[i].startTicks = 0;
		_timeouts[i].ticks = 0;
		_timeouts[i].assigned = false;
		_timeouts[i].reset = false;
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

TimeoutId Timer::newTimeout()
{
	// Timeout 0 is reserved
	for (int i = 1; i < NUM_TIMEOUTS; i++) {
		if (!_timeouts[i].assigned) {
			_timeouts[i].assigned = true;
			_timeouts[i].reset = false;
			return i;
		}
	}
	return 0;
}

TimeoutId Timer::newTimeout(uint64_t time)
{
	// Timeout 0 is reserved
	for (int i = 1; i < NUM_TIMEOUTS; i++) {
		if (!_timeouts[i].assigned) {
			_timeouts[i].startTicks = time / FRAME_MSEC + 1;
			_timeouts[i].ticks = _timeouts[i].startTicks;
			_timeouts[i].assigned = true;
			_timeouts[i].reset = false;
			return i;
		}
	}
	return 0;
}

void Timer::deleteTimeout(TimeoutId id)
{
	if (_timeouts[id].assigned) {
		_timeouts[id].ticks = 0;
		_timeouts[id].startTicks = 0;
		_timeouts[id].assigned = false;
		_timeouts[id].reset = false;
	}
}

void Timer::updateTimeout()
{
	for (int i = 1; i < NUM_TIMEOUTS; i++) {
		if (_timeouts[i].assigned) {

			if (_timeouts[i].ticks > 1) {
				_timeouts[i].ticks -= 1;

			} else if ( (_timeouts[i].ticks == 1) && _timeouts[i].reset) {
				_timeouts[i].ticks = _timeouts[i].startTicks;
				_timeouts[i].reset = false;
			}
		}
	}
}

void Timer::setTimeout(TimeoutId id, uint64_t time)
{
	if (_timeouts[id].assigned) {
		_timeouts[id].startTicks = time / FRAME_MSEC + 1;
		_timeouts[id].ticks = _timeouts[id].startTicks;
		_timeouts[id].reset = false;
	}
}

bool Timer::checkTimeout(TimeoutId id)
{
	bool ret = (_timeouts[id].ticks == 1);
	if (ret) {
		_timeouts[id].reset = true;
	}
	return ret;
}
