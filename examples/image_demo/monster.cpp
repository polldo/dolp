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
const uint8_t* monsterImages[] = {monsterImageOne, monsterImageTwo, monsterImageThree, monsterImageTwo};

const uint32_t monsterTimes[] = {100, 100, 100, 100};

const Animation monsterAnimation(monsterImages, monsterTimes, 4);

void monsterLoop(PEntity monster)
{
  if (monster.getState(MonsterAlive) == 0) {
    demo.deleteEntity(monster);
    monsterCounter--;
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

  int randX = random(100) + 10;
  int randY = random(40) + 8;
  monster.configure(randX, randY, 8, 8);

  randX = random(100) + 10;
  randY = random(40) + 8;
  monster.moveTo(randX + 10, randY + 10, 1);

  monster.collision(monsterCollision);
  monster.update(monsterLoop);

  monster.setAnimation(monsterAnimation);

  monsterCounter++;
}

