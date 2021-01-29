#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "dolp.h"

extern World demo;

enum ParticleState {
  ParticleLife
};

void spawnParticle(int x, int y);

#endif
