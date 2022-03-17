#include "particle.h"

void updateParticle(PEntity particle)
{
  TimeoutId timeout = particle.getTimeout(LiveTimeout);
  if (timer.checkTimeout(timeout)) {
    demo.deleteEntity(particle);
  }
}

void spawnParticle(int x, int y)
{
  PEntity particle = demo.newEntity();
  particle.setType(ParticleType);
  particle.update(updateParticle);
  particle.setImage(particles);
  //particle.setImage(particles8);

  particle.newTimeout(LiveTimeout, 150);

  particle.configure(x, y, 8, 8);
}

