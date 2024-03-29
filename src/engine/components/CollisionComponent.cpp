#include "CollisionComponent.h"
#include "engine/Entity.h"
#include "engine/PEntity.h"

#if defined(MICROPYTHON)
extern "C"
{
#include "dolpmodule.h"
}
#include "pentity.h"
#endif

CollisionComponent::CollisionComponent() : _entity(NULL),
                                           _onCollision(NULL)
#if defined(MICROPYTHON)
                                           ,
                                           _mpCollision(NULL)
#endif
{
}

CollisionComponent::~CollisionComponent()
{
}

void CollisionComponent::init(Entity *entity)
{
  _entity = entity;
  _onCollision = NULL;
#if defined(MICROPYTHON)
  _mpCollision = NULL;
#endif
}

void CollisionComponent::init(Entity *entity, CollisionCallback onCollision)
{
  _entity = entity;
  _onCollision = onCollision;
#if defined(MICROPYTHON)
  _mpCollision = NULL;
#endif
}

void CollisionComponent::deinit()
{
  _entity = NULL;
  _onCollision = NULL;
#if defined(MICROPYTHON)
  _mpCollision = NULL;
#endif
}

void CollisionComponent::configure(CollisionCallback onCollision)
{
  _onCollision = onCollision;
}

#if defined(MICROPYTHON)
void CollisionComponent::configure(mp_obj_t onCollision)
{
  _mpCollision = onCollision;
}
#endif

void CollisionComponent::update()
{
}

// axis-aligned bounding boxes (AABB)
bool CollisionComponent::check(Entity *entityOne, Entity *entityTwo)
{
  BodyComponent *bodyOne = entityOne->getBodyComponent();
  BodyComponent *bodyTwo = entityTwo->getBodyComponent();
  Vect2 maxOne = bodyOne->getMaxHitbox();
  Vect2 minOne = bodyOne->getMinHitbox();
  Vect2 maxTwo = bodyTwo->getMaxHitbox();
  Vect2 minTwo = bodyTwo->getMinHitbox();

  if (maxOne.x < minTwo.x - 1 || maxTwo.x < minOne.x - 1)
    return false;

  if (maxOne.y < minTwo.y - 1 || maxTwo.y < minOne.y - 1)
    return false;

  return true;
}

void CollisionComponentPool::update()
{
#if defined(POOL_DOUBLE_LINK)
  auto first = getItems();
  while (first)
  {
    auto nextFirst = static_cast<CollisionComponent *>(first->getNext());
    auto other = static_cast<CollisionComponent *>(first->getNext());
    while (other)
    {
      auto nextOther = static_cast<CollisionComponent *>(other->getNext());
      if (CollisionComponent::check(first->_entity, other->_entity))
      {
        if (first->_onCollision)
          first->_onCollision(PEntity(first->_entity), PEntity(other->_entity));
        if (other->_onCollision)
          other->_onCollision(PEntity(other->_entity), PEntity(first->_entity));
      }
      other = nextOther;
    }
    first = nextFirst;
  }
#else
  for (int i = 0; i < COLLISION_COMPONENTS_PER_WORLD - 1; i++)
  {
    if (_pool[i].isAllocated())
    {
      auto first = _pool[i];
      for (int j = i + 1; j < COLLISION_COMPONENTS_PER_WORLD; j++)
      {
        if (_pool[j].isAllocated())
        {
          auto other = _pool[j];
          if (CollisionComponent::check(first._entity, other._entity))
          {
#if defined(MICROPYTHON)
            dolp_pentity_obj_t *f = m_new_obj(dolp_pentity_obj_t);
            f->base.type = &dolp_pentity_type;
            f->pentity = PEntity(first._entity);
            dolp_pentity_obj_t *o = m_new_obj(dolp_pentity_obj_t);
            o->base.type = &dolp_pentity_type;
            o->pentity = PEntity(other._entity);
            if (first._mpCollision)
              mp_call_function_2(first._mpCollision, MP_OBJ_FROM_PTR(f), MP_OBJ_FROM_PTR(o));
            if (other._mpCollision)
              mp_call_function_2(other._mpCollision, MP_OBJ_FROM_PTR(o), MP_OBJ_FROM_PTR(f));
#else
            if (first._onCollision)
              first._onCollision(PEntity(first._entity), PEntity(other._entity));
            if (other._onCollision)
              other._onCollision(PEntity(other._entity), PEntity(first._entity));
#endif
          }
        }
      }
    }
  }
#endif
}
