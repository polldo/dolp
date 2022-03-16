#ifndef _DOLP_H_
#define _DOLP_H_

#include "Common.h"
#include "engine/Engine.h"

#define GAME_ENGINE_BEGIN (dolp.begin)
#define GAME_LOOP_BEGIN (dolp.loopBegin)
#define GAME_LOOP_END (dolp.loopEnd)

class Dolp
{
public:
    Dolp() {}
    virtual ~Dolp() {}

    void begin();
    void loopBegin();
    void loopEnd();

    PEntity newEntity();
    void deleteEntity(PEntity entity);
    // TODO: void clear();

    // Timer driver functions
    TimeoutId newTimeout();
    void deleteTimeout(TimeoutId id);
    void setTimeout(TimeoutId id, uint64_t millis, bool repeat = false);
    bool checkTimeout(TimeoutId id);
    uint64_t millis();

    // Joystick driver functions
    bool held(JoystickButton button);
    bool pressed(JoystickButton button);

    // Display driver functions
    int width();
    int height();

private:
    World _world;
};

extern Dolp dolp;

#endif //_DOLP_H_
