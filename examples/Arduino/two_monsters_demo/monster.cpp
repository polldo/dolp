#include "monster.h"

Vect2 jellySpawn(5, 5);
Vect2 ghostSpawn(120, 60);

static int monsterCounter = 0;

void monsterLoop(PEntity monster)
{
  if (monster.getState(Alive) == 0) {
    //spawnParticle(monster.getX(), monster.getY());
    demo.deleteEntity(monster);
    --monsterCounter;
    
  } else {
    Vect2 v = monster.getMovement();
    if (!v.x && !v.y) {
      int randX = random(90) + 15;
      int randY = random(40) + 10;
      monster.moveTo(randX, randY, 1);
    }
  }
}

void monsterCollision(PEntity monster, PEntity other)
{
  if (monster.getState(Type) != other.getState(Type)) {
    monster.setState(Alive, 0);
    spawnParticle(monster.getX(), monster.getY());
  }
}

void monsterSpawnSetup()
{
  // Jelly spawner
  PEntity spawner = demo.newEntity();
  spawner.configure(jellySpawn.x, jellySpawn.y, 8, 8);
  // Ghost spawner
  spawner = demo.newEntity();
  spawner.configure(ghostSpawn.x, ghostSpawn.y, 8, 8);
}

void spawnMonsters()
{
  if (monsterCounter > 40) return;
  monsterCounter += 2;

  // Jelly spawn
  PEntity monster = demo.newEntity();
  monster.setState(Alive, 1);
  monster.setState(Type, Jelly);
  monster.configure(jellySpawn.x, jellySpawn.y, 8, 8);
  int randX = random(20) + 60;
  int randY = random(40) + 30;
  monster.moveTo(randX, randY, 1);
  monster.collision(monsterCollision);
  monster.update(monsterLoop);

  // Ghost spawn
  monster = demo.newEntity();
  monster.setState(Alive, 1);
  monster.setState(Type, Ghost);
  monster.configure(ghostSpawn.x, ghostSpawn.y, 8, 8);
  randX = random(30) + 10;
  randY = random(40);
  monster.moveTo(randX, randY, 1);
  monster.collision(monsterCollision);
  monster.update(monsterLoop);
}

