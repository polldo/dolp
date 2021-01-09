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

PEntity::PEntity(Entity* entity) :
  _entity(entity)
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

void PEntity::update(UpdateCallback onUpdate)
{
  if (_entity && _entity->_updateComponent) _entity->_updateComponent->config(onUpdate);
  else if (_entity) _entity->addUpdateComponent(onUpdate);
}

void PEntity::collision()
{
  if (_entity && _entity->_collisionComponent == NULL) _entity->addCollisionComponent();
}

void PEntity::collision(CollisionCallback onCollision)
{
  if (_entity) {
    if (_entity->_collisionComponent == NULL) _entity->addCollisionComponent();
    _entity->_collisionComponent->configure(onCollision);
  }
}

bool PEntity::collided(PEntity other)
{
  if (_entity && other._entity) {
    return CollisionComponent::check(_entity, other._entity);
  }
  return false;
}

int PEntity::getState(uint8_t index)
{
  if (_entity) {
    if (_entity->_stateComponent == NULL) _entity->addStateComponent();
    return _entity->_stateComponent->getState(index);
  }
  return 0;
}

void PEntity::setState(uint8_t index, int value)
{
  if (_entity) {
    if (_entity->_stateComponent == NULL) _entity->addStateComponent();
    _entity->_stateComponent->setState(index, value);
  }  
}

void PEntity::setImage(const uint8_t* image)
{
  if (_entity) {
    _entity->_renderComponent->setImage(image);
  }
}

int PEntity::getX() 
{
  if (_entity) {
    return _entity->_bodyComponent->getPosition().x;
  }
  return 0;
}

int PEntity::getY() 
{
  if (_entity) {
    return _entity->_bodyComponent->getPosition().y;
  }
  return 0;
}

Vect2 PEntity::getPosition()
{
  if (_entity) {
    return _entity->_bodyComponent->getPosition();
  }
  return Vect2(0, 0);
}
