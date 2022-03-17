#pragma once

#include "Arduino.h"
#include "dolp.h"

#include "particle.h"

extern World demo;

enum MonsterType {
  Ghost,
  Jelly
};

enum MonsterState {
  Type = 0,
  Alive = 1
};

void monsterSpawnSetup();
void spawnMonsters();
