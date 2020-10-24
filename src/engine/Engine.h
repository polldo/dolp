#ifndef ENGINE_H
#define ENGINE_H

#include "Common.h"

#include "Entity.h"
#include "World.h"
#include "Body.h"

class Engine {
  public:
    Engine();
    ~Engine();

    void setup();
    void loop();

    void setWorld(World& world);

  private:
  World* _world;
};

extern Engine engine;

#endif // ENGINE_H
