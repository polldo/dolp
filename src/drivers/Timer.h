#ifndef REFRESH_H_
#define REFRESH_H_

#include <Common.h>

class Timer {

public:
    Timer();
    ~Timer();

    void setup();
    void waitEndFrame();
}

#endif /* REFRESH_H_ */
