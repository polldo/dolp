#if 0

#include <drivers/Timer.h>
#include <hardware/HwRefresh.h>

extern volatile uint8_t refresh_flag;

Timer::Timer()
{
}

Timer::~Timer()
{
}

void Timer::setup()
{
	hw_refresh_setup();
}

void Timer::waitEndFrame()
{
	while(!hw_refresh_get()) ;
	hw_refresh_reset();
}

#endif