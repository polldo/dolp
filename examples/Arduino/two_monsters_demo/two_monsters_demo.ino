#include <dolp.h>

#include "monster.h"

World demo;

TimeoutId spawnTimeout;

enum GameState {
  SetupState,
  PlayState
};

GameState gameState = SetupState;

void setup()
{
  // Enable Serial for debugging purposes
  Serial.begin(115200);
  while(!Serial);
  Serial.println("Start");

  GAME_ENGINE_SETUP();

  // Init random function with a random seed
  randomSeed(analogRead(0));

  engine.setWorld(demo);
}

void loop()
{
  GAME_LOOP_BEGIN();

  if (gameState == SetupState) {
    monsterSpawnSetup();
    spawnTimeout = timer.newTimeout(150);
    gameState = PlayState;

  } else if (gameState == PlayState) {
    if (timer.checkTimeout(spawnTimeout)) {
      timer.setTimeout(spawnTimeout, 1000 + random(1000));
      //timer.setTimeout(spawnTimeout, 100 + random(1000));
      spawnMonsters();
    }

  } else {
    // nothing
  }

  GAME_LOOP_END();
}
