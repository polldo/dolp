#ifndef _DOLP_H_
#define _DOLP_H_

#include "Common.h"
#include "drivers/DriverLayer.h"
#include "engine/Engine.h"

#define GAME_ENGINE_SETUP (dolp.setup)
#define GAME_LOOP_BEGIN (dolp.loopBegin)
#define GAME_LOOP_END (dolp.loopEnd)

class Dolp {
public:
    Dolp() {}
    virtual ~Dolp() {}

    void setup();
    void loopBegin();
    void loopEnd();
};

extern Dolp dolp;

#endif //_DOLP_H_
