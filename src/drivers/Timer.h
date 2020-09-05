#if 0

#ifndef REFRESH_H_
#define REFRESH_H_

#include <drivers/Common.h>

class Timer {

public:
    Timer();
    ~Timer();

    void setup();
    void waitEndFrame();
}

#endif /* REFRESH_H_ */

#endif