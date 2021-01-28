#include "bullet.h"

static void update(PEntity entity)
{
  if ( (entity.getMovement().x == 0 && entity.getMovement().y == 0)
      || entity.getState(BulletCollided)) {
    demo.deleteEntity(entity);
  }
}

void spawnBullet(int x, int y, int destX, int destY, int velocity)
{
  PEntity bullet = demo.newEntity();
  bullet.setType(BulletType);

  bullet.setState(BulletCollided, 0);

  bullet.configure(x, y, 2, 2);
  bullet.moveTo(destX, destY, velocity);
  bullet.update(update);

  bullet.setImage(laserImage);

  bullet.collision();
}
