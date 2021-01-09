#include "monster.h"

static int monsterCounter = 0;

const uint8_t monsterImageOne[] = {
  8, 8,
  0xc3, 0x18, 0x7e, 0x7e, 0x7e, 0x7e, 0x18, 0xc3
};
const uint8_t monsterImageTwo[] = {
  8, 8,
  0xc3, 0x99, 0xbd, 0xbd, 0xbd, 0xbd, 0x99, 0xc3 
};
const uint8_t monsterImageThree[] = {
  8, 8,
  0xc3, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xc3
};
const uint8_t* monsterImages[] = {monsterImageOne, monsterImageTwo, monsterImageThree};

void monsterLoop(PEntity monster)
{
  if (monster.getState(MonsterAlive) == 0) {
    demo.deleteEntity(monster);
    monsterCounter--;
  }

  // alternative: pass reference to entity state instead of its value
  int imageCounter = monster.getState(MonsterImageCounter);
  TimeoutId timeout = monster.getTimeout(MonsterFrameTimeout);
  if (timer.checkTimeout(timeout)) {
  // already possible alternative:
  // if (monster.checkTimeout(MonsterFrameTimeout)) {

    monster.setImage(monsterImages[imageCounter++]);
    if (imageCounter == 3) imageCounter = 0;
    monster.setState(MonsterImageCounter, imageCounter);
  }
}

void monsterCollision(PEntity monster, PEntity other)
{
  monster.setState(MonsterAlive, 0);
  spawnParticle(monster.getX(), monster.getY());
}

void spawnMonster()
{
  if (monsterCounter >= 30) return;

  PEntity monster = demo.newEntity();

  // Monster live flag
  monster.setState(MonsterAlive, 1);

  // Monster timeout for image refreshing
  monster.newTimeout(MonsterFrameTimeout, 140);

  // Counter for monster image update
  monster.setState(MonsterImageCounter, 0);

  int randX = random(100) + 10;
  int randY = random(40) + 8;
  monster.configure(randX, randY, 8, 8);

  randX = random(100) + 10;
  randY = random(40) + 8;
  monster.moveTo(randX + 10, randY + 10, 1);

  monster.collision(monsterCollision);
  monster.update(monsterLoop);

  monster.setImage(monsterImageOne);

  monsterCounter++;
}

