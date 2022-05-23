#include "dolp.h"

// ****************************************************************
// Image and animation definitions.
// ****************************************************************
const uint8_t playerShip[] = {16, 16, 0x00, 0x00, 0xb4, 0x00, 0x00, 0xc0, 0xfc, 0x15, 0x15, 0xfc, 0xc0, 0x00, 0x00, 0xb4, 0x00, 0x00, 0x40, 0xfc, 0x7f, 0x20, 0x38, 0x98, 0x49, 0xef, 0xef, 0x49, 0x98, 0x38, 0x20, 0x7f, 0xfc, 0x40};

const uint8_t enemy1[] = {16, 16, 0x00, 0x80, 0xc0, 0x60, 0xf5, 0x35, 0x60, 0xc8, 0xc8, 0x60, 0x35, 0xf5, 0x60, 0xc0, 0x80, 0x00, 0x00, 0x36, 0x02, 0x00, 0x1d, 0x26, 0x4c, 0x93, 0x93, 0x4c, 0x26, 0x1d, 0x00, 0x02, 0x36, 0x00};
const uint8_t enemy1Mask[] = {16, 16, 0x00, 0x80, 0xc0, 0x60, 0xff, 0xff, 0xf0, 0xf8, 0xf8, 0xf0, 0xff, 0xff, 0x60, 0xc0, 0x80, 0x00, 0x00, 0x3f, 0x03, 0x00, 0x1d, 0x3f, 0x7f, 0xff, 0xff, 0x7f, 0x3f, 0x1d, 0x00, 0x03, 0x3f, 0x00};

const uint8_t enemy2[] = {16, 16, 0x00, 0xfc, 0x46, 0x23, 0x16, 0xdc, 0xa1, 0x6e, 0x6e, 0xa1, 0xdc, 0x16, 0x23, 0x46, 0xfc, 0x00, 0x00, 0x55, 0x10, 0x0a, 0x00, 0x02, 0x08, 0x10, 0x10, 0x08, 0x02, 0x00, 0x0a, 0x10, 0x55, 0x00};
const uint8_t enemy2Mask[] = {16, 16, 0x00, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfc, 0x00, 0x00, 0x7f, 0x1f, 0x0f, 0x07, 0x07, 0x0f, 0x1f, 0x1f, 0x0f, 0x07, 0x07, 0x0f, 0x1f, 0x7f, 0x00};

const uint8_t explosion1[] = {16, 16, 0x00, 0x00, 0x00, 0x00, 0x90, 0x40, 0x40, 0x20, 0x40, 0x40, 0x84, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x05, 0x01, 0x02, 0x01, 0x21, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00};
const uint8_t explosion2[] = {16, 16, 0x00, 0x00, 0x00, 0x00, 0x88, 0x60, 0x24, 0x10, 0x20, 0x60, 0x80, 0x00, 0x12, 0x00, 0x00, 0x00, 0x00, 0x40, 0x02, 0x00, 0x00, 0x03, 0x02, 0x24, 0x02, 0x03, 0x00, 0x00, 0x00, 0x44, 0x00, 0x00};
const uint8_t explosion3[] = {16, 16, 0x00, 0x00, 0x60, 0x44, 0x84, 0x40, 0xa6, 0x14, 0x10, 0x20, 0x42, 0x82, 0x00, 0x08, 0x40, 0x00, 0x00, 0x08, 0x00, 0x08, 0x01, 0x22, 0x04, 0x4b, 0x48, 0x05, 0x02, 0x01, 0x00, 0x60, 0x06, 0x00};
const uint8_t explosion4[] = {16, 16, 0x00, 0x00, 0x00, 0x18, 0xa8, 0xc8, 0xf0, 0xf0, 0xf0, 0xe0, 0xe8, 0xb8, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x39, 0x17, 0x17, 0x1f, 0x0f, 0x17, 0x13, 0x21, 0x78, 0x20, 0x00, 0x00};
const uint8_t *explosionImages[] = {explosion1, explosion2, explosion3, explosion4};
const uint32_t explosionTimes[] = {100, 100, 100, 100};
const Animation explosionAnimation(explosionImages, explosionTimes, 4);

// ****************************************************************
// Game flow.
// ****************************************************************

// All used entity types should be defined here.
enum Types
{
  None,
  Bullet,
  EnemyOne,
  EnemyTwo
};

// Define a timeout to schedule the spawn.
TimeoutId spawnTimeout;

void setup()
{
  dolp.begin();

  spawnTimeout = dolp.newTimeout();
  dolp.setTimeout(spawnTimeout, 1000, true);
  spawnShip();

  randomSeed(analogRead(0));
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

// ****************************************************************
// Spaceship definitions.
// ****************************************************************
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
  if (dolp.pressed(ButtonA))
  {
    spawnBullet(obj.getX(), obj.getY() + shipHeight / 2);
  }
}

// ****************************************************************
// Monster definitions.
// ****************************************************************
enum EnemyState
{
  EnemyHit
};

int monsters = 0;
void spawnEnemy()
{
  if (monsters > 4)
  {
    return;
  }

  PEntity obj = dolp.newEntity();
  monsters++;
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

// ****************************************************************
// Bullet definitions.
// ****************************************************************
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

// ****************************************************************
// Explosion definitions.
// ****************************************************************
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
