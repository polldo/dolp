#include "hardware/HwConfiguration.h"
#if defined (_STM32_DUINO_)

#include <hardware/HwRefresh.h>
#include <HardwareTimer.h>

#define REFRESH_TIMER (TIM5)
HardwareTimer _refreshTimer (REFRESH_TIMER);

volatile bool _refreshFlag = false;
void refreshCallback();

void refreshCallback()
{
	_refreshFlag = true;
}

void hwRefreshSetup()
{
    _refreshTimer.setMode(1, TIMER_OUTPUT_COMPARE);  
    _refreshTimer.attachInterrupt(refreshCallback);
	_refreshTimer.setOverflow(30, HERTZ_FORMAT); 
	_refreshTimer.resume();
}

bool hwRefreshGet()
{
	return _refreshFlag;
}

void hwRefreshReset()
{
	_refreshFlag = false;
}

#endif
