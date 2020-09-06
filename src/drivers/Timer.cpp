#include <drivers/Timer.h>
#include <hardware/HwRefresh.h>

Timer::Timer()
{
}

Timer::~Timer()
{
}

void Timer::setup()
{
	hwRefreshSetup();
}

void Timer::waitEndFrame()
{
	while(!hwRefreshGet()) ;
	hwRefreshReset();
}
