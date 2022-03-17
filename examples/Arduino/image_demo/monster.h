#ifndef MONSTER_H_
#define MONSTER_H_

#include "Arduino.h"
#include "dolp.h"

#include "particle.h"

enum MonsterState
{
  MonsterAlive = 0,
  MonsterImageCounter = 1
};

enum MonsterTimeout
{
  MonsterFrameTimeout,
};

void spawnMonster();

#endif
