#include "hardware/HwConfiguration.h"
#if defined(MICROPYTHON)

#include "hardware/HwRefresh.h"
#include "Common.h"

extern "C"
{
#include "py/runtime.h"
#include <extmod/machine_spi.h>
#include <ports/rp2/modmachine.h>
#include <py/obj.h>
#include <py/mphal.h>
}

#include <stdlib.h>
#include <cstring>
#include <string>

void hwRefreshSetup()
{
}

void hwRefreshWaitEndFrame()
{
  static const int timeout = FRAME_MSEC;
  static auto time = mp_hal_ticks_ms();

  auto waitTime = timeout - int(mp_hal_ticks_ms() - time);
#ifdef PROFILING
  std::string s = std::to_string(waitTime) + "\n\r";
  const char *str = s.c_str();
  mp_hal_stdout_tx_str(str);
#endif

  if (waitTime > 0)
  {
    mp_hal_delay_ms(mp_uint_t(waitTime));
  }

  time = mp_hal_ticks_ms();
}

#endif
