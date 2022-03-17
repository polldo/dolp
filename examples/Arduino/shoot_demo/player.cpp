#include "player.h"
#include "bullet.h"
#include <math.h>

static TimeoutId shootTimeout;

static int angle = 0;
static int range = 45;
static int bulletVelocity = 10;

const int dAngle = 5;

static void shoot(int originX, int originY) {
  float rad = (angle * 71) / 4068.;
  double pX = (double)(range) * cos(rad);
  double pY = (double)(range) * sin(rad);
  int destX = originX + (int)pX;
  int destY = originY + (int)pY;
  spawnBullet(originX, originY, destX, destY, bulletVelocity);
}

static void update(PEntity player)
{
  if (joystick.held(ButtonA)) {
    angle = (angle + dAngle) % 360;

  } else if (joystick.pressed(ButtonB)) {
    angle = (angle - dAngle) % 360;
  }

  if (timer.checkTimeout(shootTimeout)) {
    shoot(player.getX(), player.getY());
  }
}

void spawnPlayer()
{
  PEntity player = demo.newEntity();
  player.setType(PlayerType);

  player.configure(display.width()/2, display.height()/2, 23, 23);
  player.update(update);

  player.collision();

  player.setImage(spaceshipImage);

  shootTimeout = timer.newTimeout(100);
}
