#include <dolp.h>

World demo;

#define MAX_MONSTERS (100)
PEntity monsters[MAX_MONSTERS];

void setup()
{
  Serial.begin(115200);
  while(!Serial);
  Serial.println("Start");

  GAME_ENGINE_SETUP();

  randomSeed(analogRead(0));

  engine.setWorld(demo);
}

void clearMonsters()
{
  for (int i = 0; i < MAX_MONSTERS; i++) {
    demo.deleteEntity(monsters[i]);
  }
}

void spawnMonster()
{
  static uint8_t monstersIndex = 0;

  if (monstersIndex == MAX_MONSTERS) {
    clearMonsters();
    monstersIndex = 0;
  }

  PEntity monster = demo.newEntity();
  int randX = random(100) + 10;
  int randY = random(40) + 8;
  monster.configure(randX, randY, 5, 5);
  monsters[monstersIndex++] = monster;
}

void loop()
{
  static uint64_t timeRef = 0;

  GAME_LOOP_BEGIN();

  if (joystick.pressed(ButtonA)) {

  }

  if (timer.getMilliseconds() > timeRef + 100) {
    timeRef = timer.getMilliseconds();
    spawnMonster();
  }

  GAME_LOOP_END();
}
