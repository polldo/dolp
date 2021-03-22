#include <dolp.h>
#include "Common.h"
#include "Multiplayer.h"

#include "Paddle.h"
#include "Ball.h"

//#include "ArduinoBLE.h"

World demo;

GameState gameState = SetupState;

uint8_t syncValue;

void setup()
{
  // Enable Serial for debugging purposes
  Serial.begin(115200);
  //while(!Serial);
  Serial.println("Start");

  clientBegin();

  GAME_ENGINE_SETUP();

  // Init random function with a random seed
  //randomSeed(analogRead(0));
  randomSeed(10);

  engine.setWorld(demo);

  syncValue = clientSync();
}

void loop()
{
  //BLE.poll();
  //GAME_LOOP_BEGIN();
  joystick.update();
  //syncValue = clientSync();
  syncValue = clientSync();
  engine.loopBegin();

  if (gameState == SetupState) {
    spawnPaddle();
    spawnField();
    spawnBall();
    gameState = PlayState;

  } else if (gameState == PlayState) {
    //clientSync();

  } else if (gameState == GameOverState) {
    Serial.println("Game over");
    demo.clear();

  } else {
    // nothing
  }

  GAME_LOOP_END();
}

void spawnField()
{
  PEntity wall = demo.newEntity();
  wall.setType(WallType);
  wall.configure(display.width()/2, 1, display.width(), 2);
  wall.collision();

  wall = demo.newEntity();
  wall.setType(WallType);
  wall.configure(display.width()/2, display.height()-1, display.width(), 2);
  wall.collision();
}
