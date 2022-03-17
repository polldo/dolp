#include <dolp.h>

#include "monster.h"
#include "particle.h"

World demo;

TimeoutId spawnTimeout;

void setup()
{
  // Enable Serial for debugging purposes
  Serial.begin(115200);
  // while (!Serial)
  //   ;
  Serial.println("Start");

  // Init random function with a random seed
  randomSeed(analogRead(0));

  dolp.begin();
  spawnTimeout = dolp.newTimeout();
  dolp.setTimeout(spawnTimeout, 150, true);
}

void loop()
{
  dolp.loopBegin();

  if (dolp.checkTimeout(spawnTimeout))
  {
    spawnMonster();
  }

  dolp.loopEnd();
}
