#include "UpdateComponent.h"
#include "engine/Entity.h"
#include "engine/PEntity.h"

#if defined(MICROPYTHON)
extern "C"
{
#include "dolpmodule.h"
}
#include "pentity.h"
#endif

UpdateComponent::UpdateComponent() : _entity(NULL),
                                     _update(NULL)
{
}

UpdateComponent::~UpdateComponent()
{
}

void UpdateComponent::init(Entity *entity, UpdateCallback callback)
{
  _entity = entity;
  _update = callback;
}

void UpdateComponent::config(UpdateCallback callback)
{
  _update = callback;
}

void UpdateComponent::deinit()
{
  _entity = NULL;
  _update = NULL;
}

#if defined(MICROPYTHON)
void UpdateComponent::config(mp_obj_t callback)
{
  _mpUpdate = callback;
}
#endif

void UpdateComponentPool::update()
{
#if defined(POOL_DOUBLE_LINK)
  auto component = getItems();
  while (component)
  {
    auto nextComponent = static_cast<UpdateComponent *>(component->getNext());
    component->_update(PEntity(component->_entity));
    component = nextComponent;
  }
#else
  for (int i = 0; i < UPDATE_COMPONENTS_PER_WORLD; i++)
  {
    if (_pool[i].isAllocated())
    {
#if defined(MICROPYTHON)
      // auto ent = PEntity(_pool[i]._entity);
      dolp_pentity_obj_t *p = m_new_obj(dolp_pentity_obj_t);
      p->base.type = &dolp_pentity_type;
      p->pentity = PEntity(_pool[i]._entity);
      mp_call_function_1(_pool[i]._mpUpdate, MP_OBJ_FROM_PTR(p));
#else
      _pool[i]._update(PEntity(_pool[i]._entity));
#endif
    }
  }
#endif
}
