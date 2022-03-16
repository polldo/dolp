#ifndef COLLISION_COMPONENT_H
#define COLLISION_COMPONENT_H

#ifndef COLLISION_COMPONENTS_PER_WORLD
#define COLLISION_COMPONENTS_PER_WORLD (200)
#endif

#include "Common.h"
#include "engine/Pool.h"

class PEntity;
class Entity;

typedef void (*CollisionCallback)(PEntity entity, PEntity other);

// TODO: template for layering -> one pool for each different layer of collisions

class CollisionComponent : public Poolable
{
public:
  CollisionComponent();
  virtual ~CollisionComponent();

  void configure(CollisionCallback onCollision);

  static bool check(Entity *entityOne, Entity *entityTwo);

protected:
  friend class Entity;
  void init(Entity *entity);
  void init(Entity *entity, CollisionCallback onCollision);
  void deinit();

  void update();

private:
  friend class CollisionComponentPool;
  friend class Entity;
  Entity *_entity;
  CollisionCallback _onCollision;
};

class CollisionComponentPool : public Pool<CollisionComponent, COLLISION_COMPONENTS_PER_WORLD>
{
public:
  void update();
};

#endif
