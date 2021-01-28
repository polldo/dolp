#include "monster.h"

static int monsterCounter = 0;

void spawnSatellites();

void monsterUpdate(PEntity monster)
{
  if (monster.getState(Alive) == 0) {
    spawnParticle(monster.getX(), monster.getY());
    if (random(0, 2)) {
      spawnSatellites();
    }
    demo.deleteEntity(monster);
    --monsterCounter;
    
  } else {
    Vect2 v = monster.getMovement();
    if ( (v.x == 0) && (v.y == 0) ) {
      int randX = random(display.width() - 20) + 15;
      int randY = random(display.height() - 20) + 10;
      monster.moveTo(randX, randY, 1);
    }
  }
}

void monsterCollision(PEntity monster, PEntity other)
{
  //if (monster.getType() != other.getType()) {
  if (other.getType() == BulletType) {
    monster.setState(Alive, 0);
    spawnParticle(monster.getX(), monster.getY());

  } else if (other.getType() == PlayerType) {
    monster.setState(Alive, 0);
    //gameState = GameOverState;
  }
}

void calculateExtremeCoordinates(int& x, int& y)
{
  // right 
  if (random(0, 2)) {
    x = random(20) + display.width() - 18;
  //left
  } else {
    x = random(20);
  }

  // top
  if (random(0, 2)) {
    y = random(10) + display.height() - 15;
  // bottom
  } else {
    y = random(10);
  }
}

void spawnMonster()
{
  if (monsterCounter > 40) return;
  ++monsterCounter;

  PEntity monster = demo.newEntity();
  monster.setType(MonsterType);
  monster.setState(Alive, 1);

  int randX, randY;
  calculateExtremeCoordinates(randX, randY);
  monster.configure(randX, randY, 16, 16);
  int randVel = random(10);
  monster.moveTo(display.width()/2, display.height()/2, randVel);
  monster.collision(monsterCollision);
  monster.update(monsterUpdate);

  monster.setImage(asteroidImage);
}

void spawnSatellites()
{

}

