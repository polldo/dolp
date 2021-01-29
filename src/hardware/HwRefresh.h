#ifndef HW_REFRESH_H_
#define HW_REFRESH_H_

#include "Common.h"

#ifndef FPS
#define FPS 30
#define FRAME_MSEC 33
#endif

void hwRefreshSetup();
void hwRefreshWaitEndFrame();

#endif /* HW_REFRESH_H_ */
