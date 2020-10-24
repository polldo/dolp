#include "Engine.h"

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
  // clearDisplay();
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
