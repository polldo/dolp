#ifndef BODY_COMPONENT_H
#define BODY_COMPONENT_H

#ifndef BODY_COMPONENTS_PER_WORLD
#define BODY_COMPONENTS_PER_WORLD (200)
#endif

#include "Common.h"
#include "engine/Pool.h"

class Entity;

struct Vect2 {
  Vect2() {}
  Vect2(int inputX, int inputY) : x(inputX), y(inputY) {}

  void set(int inputX, int inputY) 
  {
    x = inputX;
    y = inputY;
  }

  int x, y;
};

class BodyComponent : public Poolable {
  public:
    BodyComponent();
    virtual ~BodyComponent();

    void configure(int x, int y, int width, int height);
    Vect2& getPosition();
    Vect2& getSize();

    //void update();

  protected:
    friend class Entity;
    void init(Entity* entity);
    void init(Entity* entity, int x, int y, int w, int h);
    void deinit();

  private:
    Entity* _entity;
    Vect2 _position;
    Vect2 _size;
};

class BodyComponentPool : public Pool<BodyComponent, BODY_COMPONENTS_PER_WORLD> {
  public: 
    void update()
    {
      for (int i = 0; i < BODY_COMPONENTS_PER_WORLD; i++) {
        if (_pool[i].isAllocated()) {
          //_pool[i].update();
        }
      }
    }
};

#endif 
