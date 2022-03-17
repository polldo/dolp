#include "medusa.h"

static int medusaCounter = 0;

void medusaLoop(PEntity medusa)
{
  if (medusa.getState(MedusaAlive) == 0)
  {
    dolp.deleteEntity(medusa);
    medusaCounter--;
  }
}

void medusaCollision(PEntity medusa, PEntity other)
{
  medusa.setState(MedusaAlive, 0);
  spawnParticle(medusa.getX(), medusa.getY());
}

void spawnMedusa()
{
  if (medusaCounter >= 30)
    return;

  PEntity medusa = dolp.newEntity();

  // Monster live flag
  medusa.setState(MedusaAlive, 1);

  int randX = random(100) + 10;
  int randY = random(40) + 8;
  medusa.configure(randX, randY, 8, 8);

  randX = random(100) + 10;
  randY = random(40) + 8;
  medusa.moveTo(randX + 10, randY + 10, 1);

  medusa.collision(medusaCollision);
  medusa.update(medusaLoop);

  medusaCounter++;
}
