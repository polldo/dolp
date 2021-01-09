#ifndef MONSTER_H_
#define MONSTER_H_

#include "Arduino.h"
#include "dolp.h"

#include "particle.h"

extern World demo;

enum MonsterState {
  MonsterAlive = 0,
  MonsterFrameTimeout = 1,
  MonsterImageCounter = 2
};

void spawnMonster();

#endif
