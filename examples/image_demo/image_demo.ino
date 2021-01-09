#include <dolp.h>

#include "monster.h"
#include "particle.h"

World demo;

int spawnTimeout = 0;

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

  spawnTimeout = timer.newTimeout();
  timer.refreshTimeout(spawnTimeout, 500);
}

void loop()
{
  GAME_LOOP_BEGIN();

  if (joystick.pressed(ButtonA)) {

  }

  if (timer.checkTimeout(spawnTimeout)) {
    spawnMonster();
    timer.refreshTimeout(spawnTimeout, 150);
  }

  GAME_LOOP_END();
}
