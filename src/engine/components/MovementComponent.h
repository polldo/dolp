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

    void configure(Vect2 destination, int speed);
    void configure(int x, int y, int speed);
    void update();

  protected:
    friend class Entity;
    void init(Entity* entity);
    void init(Entity* entity, BodyComponent* bodyComponent);
    void deinit();

  private:
    Entity* _entity;
    BodyComponent* _bodyComponent;
    //int _x, _y;
    Vect2 _destination;
    Vect2 _direction;
    //int _speed;
    int _dS;

    //Time deltaTime;
};

class MovementComponentPool : public Pool<MovementComponent, MOVEMENT_COMPONENTS_PER_WORLD> {
  public: 
    void update()
    {
      for (int i = 0; i < MOVEMENT_COMPONENTS_PER_WORLD; i++) {
        if (_pool[i].isAllocated()) {
          _pool[i].update();
        }
      }
      // Alternative
      //auto component = _headAllocated;
      //while (component) {
        //component->update();
        //component = component->getNext();
      //}
    }
};

#endif 
