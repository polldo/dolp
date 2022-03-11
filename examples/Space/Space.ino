#include "dolp.h"
#include "images.h"

TimeoutId spawnTimeout;
int monsters = 0;

void setup()
{
  dolp.begin();

  // Init random function with a random seed
  randomSeed(analogRead(0));

  spawnShip();
  spawnTimeout = dolp.newTimeout();
  dolp.setTimeout(spawnTimeout, 1000, true);
}

void loop()
{
  dolp.loopBegin();

  if (dolp.checkTimeout(spawnTimeout))
  {
    spawnEnemy();
  }

  dolp.loopEnd();
}

const int shipWidth = 16, shipHeight = 16;
void spawnShip()
{
  PEntity obj = dolp.newEntity();
  obj.configure(dolp.width() / 2, shipHeight / 2, shipWidth, shipHeight);
  obj.update(shipUpdate);
  obj.setImage(playerShip);
}

void shipUpdate(PEntity obj)
{
  if (dolp.pressed(ButtonC))
  {
    spawnBullet(obj.getX(), obj.getY() + shipHeight / 2);
  }
}

enum Types
{
  Bullet,
  EnemyOne,
  EnemyTwo
};

enum EnemyState
{
  EnemyHit
};

void spawnEnemy()
{
  if (monsters > 4)
  {
    return;
  }

  PEntity obj = dolp.newEntity();
  monsters++;
  // obj.configure(display.width() / 2, display.height() / 2, 16, 16);
  obj.configure(0, display.height() - 8, 16, 16);
  obj.update(enemyUpdate);
  obj.collision(enemyCollision);
  obj.setState(EnemyHit, 0);

  obj.setType(EnemyTwo);
  obj.setImage(enemy2, enemy2Mask);
  if (random(2) == 1)
  {
    obj.setType(EnemyOne);
    obj.setImage(enemy1, enemy1Mask);
  }
}

void enemyCollision(PEntity obj, PEntity other)
{
  if (obj.getState(EnemyHit))
    return;
  if (other.getType() != Bullet)
    return;
  dolp.deleteEntity(obj);
  dolp.deleteEntity(other);
  explosion(obj.getX(), obj.getY());
  obj.setState(EnemyHit, 1);
  monsters--;
}

void enemyUpdate(PEntity obj)
{
  if (!obj.isMoving())
  {
    int randX = random(100) + 10;
    int randY = random(40) + shipHeight + 8;
    obj.moveTo(randX, randY, 5);
  }
}

const int bulletWidth = 2, bulletHeight = 4;
const int bulletSpeed = 10;
void spawnBullet(int x, int y)
{
  PEntity obj = dolp.newEntity();
  obj.setType(Bullet);
  obj.configure(x, y, bulletWidth, bulletHeight);
  obj.update(bulletUpdate);
  obj.moveTo(x, dolp.height() - 10, bulletSpeed);
  obj.collision();
}

void bulletUpdate(PEntity obj)
{
  if (!obj.isMoving())
  {
    dolp.deleteEntity(obj);
  }
}

enum ExplosionTimeout
{
  LiveTimeout
};

void explosion(int x, int y)
{
  PEntity obj = dolp.newEntity();
  obj.configure(x, y, 0, 0);
  auto t = obj.newTimeout(LiveTimeout);
  dolp.setTimeout(t, 400, false);
  obj.setAnimation(explosionAnimation);
  obj.update(explosionUpdate);
}

void explosionUpdate(PEntity obj)
{
  auto t = obj.getTimeout(LiveTimeout);
  if (dolp.checkTimeout(t))
  {
    dolp.deleteEntity(obj);
  }
}
