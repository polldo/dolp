#ifndef BODY_COMPONENT_H
#define BODY_COMPONENT_H

#ifndef BODY_COMPONENTS_PER_WORLD
#define BODY_COMPONENTS_PER_WORLD (200)
#endif

#include "Common.h"
#include "engine/Pool.h"

class Entity;

struct Vect2
{
  Vect2() {}
  Vect2(int inputX, int inputY) : x(inputX), y(inputY) {}

  void set(int inputX, int inputY)
  {
    x = inputX;
    y = inputY;
  }

  int x, y;
};

class BodyComponent : public Poolable
{
public:
  BodyComponent();
  virtual ~BodyComponent();

  void configure(int x, int y, int width, int height);
  Vect2 &getPosition();
  Vect2 &getSize();
  Vect2 &getMaxHitbox();
  Vect2 &getMinHitbox();

  void update();

protected:
  friend class Entity;
  void init(Entity *entity);
  void init(Entity *entity, int x, int y, int w, int h);
  void deinit();

private:
  Entity *_entity;
  Vect2 _position;
  Vect2 _size;

  Vect2 _minHitbox;
  Vect2 _maxHitbox;
};

class BodyComponentPool : public Pool<BodyComponent, BODY_COMPONENTS_PER_WORLD>
{
public:
  void update()
  {
#if defined(POOL_DOUBLE_LINK)
    auto component = getItems();
    while (component)
    {
      component->update();
      component = static_cast<BodyComponent *>(component->getNext());
    }
#else
    for (int i = 0; i < BODY_COMPONENTS_PER_WORLD; i++)
    {
      if (_pool[i].isAllocated())
      {
        _pool[i].update();
      }
    }
#endif
  }
};

#endif
