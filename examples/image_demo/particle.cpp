#include "particle.h"

const uint8_t particles[] = {
  8, 8,
  0xf7, 0xbe, 0xff, 0xf7, 0x5f, 0xfe, 0xf7, 0xbd
};

void updateParticle(PEntity particle)
{
  int life = particle.getState(ParticleLife);
  life -= 1; 
  if (!life) demo.deleteEntity(particle);
  else particle.setState(ParticleLife, life);
}

void spawnParticle(int x, int y)
{
  PEntity particle = demo.newEntity();
  particle.update(updateParticle);
  particle.setState(ParticleLife, 5);
  particle.setImage(particles);

  particle.configure(x, y, 8, 8);
}

