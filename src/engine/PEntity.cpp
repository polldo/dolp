#include "Common.h"
#include "PEntity.h"

PEntity::PEntity() :
  _entity(NULL)
{
}

PEntity::PEntity(Entity& entity) :
  _entity(&entity)
{
}

PEntity::~PEntity()
{
}

void PEntity::configure(int x, int y, int width, int height)
{
  if (_entity) {
    _entity->_bodyComponent->configure(x, y, width, height);
  }
}

int PEntity::getId()
{
  if (_entity) {
    return _entity->_id;
  }
  return -1;
}

void PEntity::moveTo(int x, int y, int speed)
{
  if (_entity && _entity->_movementComponent) _entity->_movementComponent->configure(Vect2(x, y), speed);
  else if (_entity) {
    _entity->addMovementComponent();
    _entity->_movementComponent->configure(Vect2(x, y), speed);
  }
}
