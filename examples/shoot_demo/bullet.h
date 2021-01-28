#ifndef BULLET_H_
#define BULLET_H_

#include "Arduino.h"
#include "dolp.h"
#include "common.h"

enum BulletState {
  BulletCollided
};

void spawnBullet(int x, int y, int destX, int destY, int velocity);

const uint16_t laserImage[] {
  3,4,
  0xeadc, 0xf2a2, 0xea5b, 
  0xe21a, 0xfaaf, 0xe199, 
  0xb995, 0xeaaf, 0xb915, 
  0xb194, 0xdaed, 0xb114
};

#endif
