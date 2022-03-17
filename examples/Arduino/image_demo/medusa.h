#ifndef MEDUSA_H_
#define MEDUSA_H_

#include "Arduino.h"
#include "dolp.h"

#include "particle.h"

enum MedusaState
{
  MedusaAlive = 0,
  MedusaImageCounter = 1
};

enum MedusaTimeout
{
  MedusaFrameTimeout,
};

void spawnMedusa();

#endif
