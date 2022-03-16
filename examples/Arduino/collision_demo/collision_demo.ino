#include <dolp.h>

static int monsterCounter = 0;
TimeoutId spawnTimeout;

void setup()
{
  Serial.begin(115200);
  // while (!Serial)
  //   ;
  Serial.println("Start");

  dolp.begin();
  // Init random function with a random seed
  randomSeed(analogRead(0));
  spawnTimeout = dolp.newTimeout();
  dolp.setTimeout(spawnTimeout, 500, true);
}

void loop()
{
  dolp.loopBegin();

  if (dolp.checkTimeout(spawnTimeout))
  {
    spawnMonster();
  }

  dolp.loopEnd();
}

void spawnMonster()
{
  if (monsterCounter >= 30)
    return;

  PEntity monster = dolp.newEntity();
  int randX = random(100) + 10;
  int randY = random(40) + 8;
  monster.configure(randX, randY, 8, 8);
  monster.collision(monsterCollision);
  monster.update(monsterLoop);
  monsterCounter++;
}

void monsterLoop(PEntity monster)
{
  if (!monster.isMoving())
  {
    int randX = random(100) + 10;
    int randY = random(40) + 8;
    monster.moveTo(randX + 10, randY + 10, 4);
  }
}

void monsterCollision(PEntity monster, PEntity other)
{
  dolp.deleteEntity(monster);
  spawnParticle(monster.getX(), monster.getY());
  monsterCounter--;
}

enum ParticleTimeout
{
  LiveTimeout
};

const uint8_t particles[] = {8, 8, 0xf7, 0xbe, 0xff, 0xf7, 0x5f, 0xfe, 0xf7, 0xbd};

void updateParticle(PEntity particle)
{
  TimeoutId timeout = particle.getTimeout(LiveTimeout);
  if (dolp.checkTimeout(timeout))
  {
    dolp.deleteEntity(particle);
  }
}

void spawnParticle(int x, int y)
{
  PEntity particle = dolp.newEntity();
  particle.update(updateParticle);
  particle.setImage(particles);
  TimeoutId tm = particle.newTimeout(LiveTimeout);
  dolp.setTimeout(tm, 150);
  particle.configure(x, y, 8, 8);
}
