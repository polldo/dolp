#ifndef MOVEMENT_COMPONENT_H
#define MOVEMENT_COMPONENT_H

#ifndef MOVEMENT_COMPONENTS_PER_WORLD
#define MOVEMENT_COMPONENTS_PER_WORLD (40)
#endif

#include "Common.h"
#include "engine/Pool.h"
#include "BodyComponent.h"

class Entity;

class MovementComponent : public Poolable {
  public:
    MovementComponent();
    virtual ~MovementComponent();

    void configure(int x, int y, int velocity);
    void configure(Vect2 destination, int velocity);
    void update();

    Vect2& getMovement();

  protected:
    friend class Entity;
    void init(Entity* entity);
    void init(Entity* entity, BodyComponent* bodyComponent);
    void deinit();

  private:
    Entity* _entity;
    BodyComponent* _bodyComponent;
    Vect2 _destination;
    Vect2 _movement;
    int _movedX, _movedY;
};

class MovementComponentPool : public Pool<MovementComponent, MOVEMENT_COMPONENTS_PER_WORLD> {
  public: 
    void update()
    {
#if defined (POOL_DOUBLE_LINK)
      auto component = getItems();
      while (component) {
        component->update();
        component = static_cast<MovementComponent*>(component->getNext());
      }
#else
      for (int i = 0; i < MOVEMENT_COMPONENTS_PER_WORLD; i++) {
        if (_pool[i].isAllocated()) {
          _pool[i].update();
        }
      }
#endif
    }
};

#endif 
