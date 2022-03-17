#include "particle.h"

const uint8_t particles[] = {
  8, 8,
  0xf7, 0xbe, 0xff, 0xf7, 0x5f, 0xfe, 0xf7, 0xbd
};

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
  particle.update(updateParticle);
  particle.setImage(particles);

  particle.newTimeout(LiveTimeout, 150);

  particle.configure(x, y, 8, 8);
}

