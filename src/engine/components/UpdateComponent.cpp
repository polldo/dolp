#include "UpdateComponent.h"
#include "engine/Entity.h"
#include "engine/PEntity.h"

UpdateComponent::UpdateComponent() :
  _entity(NULL),
  _update(NULL)
{
}

UpdateComponent::~UpdateComponent()
{
}

void UpdateComponent::init(Entity* entity, UpdateCallback callback)
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

void UpdateComponentPool::update()
{
#if defined (POOL_DOUBLE_LINK)
  auto component = getItems();
  while (component) {
    auto nextComponent = static_cast<UpdateComponent*>(component->getNext());
    component->_update(PEntity(component->_entity));
    component = nextComponent;
  }
#else
  for (int i = 0; i < UPDATE_COMPONENTS_PER_WORLD; i++) {
    if (_pool[i].isAllocated()) {
      _pool[i]._update(PEntity(_pool[i]._entity));
    }
  }
#endif
}
