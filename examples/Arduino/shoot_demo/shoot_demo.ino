#include <dolp.h>

#include "monster.h"
#include "player.h"
#include "common.h"

World demo;

GameState gameState = SetupState;

TimeoutId monsterTimeout;

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
    spawnPlayer();
    gameState = PlayState;
    monsterTimeout = timer.newTimeout(500);

  } else if (gameState == PlayState) {
    if (timer.checkTimeout(monsterTimeout)) {
      timer.setTimeout(monsterTimeout, random(1000));
      spawnMonster();
    }

  } else if (gameState == GameOverState) {
    Serial.println("Game over");
    demo.clear();

  } else {
    // nothing
  }

  GAME_LOOP_END();
}
