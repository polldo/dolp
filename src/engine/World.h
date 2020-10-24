#ifndef WORLD_H
#define WORLD_H

#include "Entity.h"
#include "Body.h"

class World {
  public:
    World();
    virtual ~World();

    void clear();

    PEntity newEntity();
    void deleteEntity(PEntity entity);

    //void update();
    void render();

  private:
  EntityPool _entities;

  // _visibleBodies[BODIES_PER_WORLD];
  // MovementComponent _movements[MOVEMENTS_PER_WORLD];
};

#endif // WORLD_H
