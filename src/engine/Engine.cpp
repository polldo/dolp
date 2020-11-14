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

void Engine::loop()
{
  // Update world

  // Draw world
  //clearDisplay();
  display.fill(0);
  if (_world) {
    _world->update();
    _world->render();
  }
}

// setActiveWorld
void Engine::setWorld(World& world)
{
  _world = &world;
}

Engine engine;
