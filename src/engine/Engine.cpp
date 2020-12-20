#include "Engine.h"

#include "drivers/DriverLayer.h"

Engine::Engine() :
  _world(NULL)
{
}

Engine::~Engine()
{
}

void Engine::setup()
{
}

void Engine::loopBegin()
{
  // Update world
  if (_world) {
    _world->update();
  }
}

void Engine::loopEnd()
{
  // Draw world
  //clearDisplay();
  display.fill(BLACK_COLOR);
  if (_world) {
    _world->render();
  }
}

// setActiveWorld
void Engine::setWorld(World& world)
{
  _world = &world;
}

Engine engine;
