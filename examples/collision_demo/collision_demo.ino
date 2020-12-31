#include <dolp.h>

World demo;

enum MonsterState {
  MonsterAlive = 0
};

static int monsterCounter = 0;

void setup()
{
  // Enable Serial for debugging purposes
  Serial.begin(115200);
  while(!Serial);
  Serial.println("Start");

  GAME_ENGINE_SETUP();

  // Init random function with a random seed
  randomSeed(analogRead(0));

  engine.setWorld(demo);
}

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
}

void spawnMonster()
{
  if (monsterCounter >= 30) return;

  PEntity monster = demo.newEntity();

  monster.setState(MonsterAlive, 1);

  int randX = random(100) + 10;
  int randY = random(40) + 8;
  monster.configure(randX, randY, 5, 5);

  randX = random(100) + 10;
  randY = random(40) + 8;
  monster.moveTo(randX + 10, randY + 10, 1);

  monster.collision(monsterCollision);
  monster.update(monsterLoop);

  monsterCounter++;
}

void loop()
{
  static uint64_t timeRef = 0;

  GAME_LOOP_BEGIN();

  if (joystick.pressed(ButtonA)) {

  }

  if (timer.getMilliseconds() > timeRef + 500) {
    timeRef = timer.getMilliseconds();
    spawnMonster();
  }

  GAME_LOOP_END();
}
