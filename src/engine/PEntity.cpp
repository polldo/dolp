#include "Common.h"
#include "PEntity.h"

PEntity::PEntity() : _entity(NULL)
{
}

PEntity::PEntity(Entity &entity) : _entity(&entity)
{
}

PEntity::PEntity(Entity *entity) : _entity(entity)
{
}

PEntity::~PEntity()
{
}

void PEntity::configure(int x, int y, int width, int height)
{
  if (_entity)
  {
    _entity->_bodyComponent->configure(x, y, width, height);
  }
}

int PEntity::getId()
{
  if (_entity)
  {
    return _entity->_id;
  }
  return -1;
}

uint8_t PEntity::getType()
{
  if (_entity)
  {
    return _entity->_type;
  }
  return 0xFF;
}

void PEntity::setType(uint8_t entityType)
{
  if (_entity)
  {
    _entity->_type = entityType;
  }
}

void PEntity::moveTo(int x, int y, int velocity)
{
  if (_entity && _entity->_movementComponent)
    _entity->_movementComponent->configure(x, y, velocity);
  else if (_entity)
  {
    _entity->addMovementComponent();
    _entity->_movementComponent->configure(x, y, velocity);
  }
}

Vect2 PEntity::getMovement()
{
  if (_entity && _entity->_movementComponent)
  {
    return _entity->_movementComponent->getMovement();
  }
  return (Vect2(0, 0));
}

bool PEntity::isMoving()
{
  Vect2 mov = getMovement();
  return (mov.x != 0 || mov.y != 0);
}

void PEntity::update(UpdateCallback onUpdate)
{
  if (_entity && _entity->_updateComponent)
    _entity->_updateComponent->config(onUpdate);
  else if (_entity)
    _entity->addUpdateComponent(onUpdate);
}

void PEntity::collision()
{
  if (_entity && _entity->_collisionComponent == NULL)
    _entity->addCollisionComponent();
}

void PEntity::collision(CollisionCallback onCollision)
{
  if (_entity)
  {
    if (_entity->_collisionComponent == NULL)
      _entity->addCollisionComponent();
    _entity->_collisionComponent->configure(onCollision);
  }
}

bool PEntity::collided(PEntity other)
{
  if (_entity && other._entity)
  {
    return CollisionComponent::check(_entity, other._entity);
  }
  return false;
}

int PEntity::getState(uint8_t index)
{
  if (_entity)
  {
    if (_entity->_stateComponent == NULL)
      _entity->addStateComponent();
    return _entity->_stateComponent->getState(index);
  }
  return 0;
}

void PEntity::setState(uint8_t index, int value)
{
  if (_entity)
  {
    if (_entity->_stateComponent == NULL)
      _entity->addStateComponent();
    _entity->_stateComponent->setState(index, value);
  }
}

void PEntity::setImage(const uint8_t *image)
{
  if (_entity)
  {
    _entity->_renderComponent->setImage(image);
  }
}

void PEntity::setImage(const uint16_t *image)
{
  if (_entity)
  {
    _entity->_renderComponent->setImage(image);
  }
}

void PEntity::setAnimation(const Animation &animation)
{
  if (_entity)
  {
    _entity->_renderComponent->setAnimation(animation);
  }
}

void PEntity::newTimeout(uint8_t index, uint64_t time)
{
  if (_entity)
  {
    _entity->_timeComponent.init(index, time);
  }
}

bool PEntity::checkTimeout(uint8_t index)
{
  if (_entity)
  {
    return _entity->_timeComponent.checkTimeout(index);
  }
  return false;
}

TimeoutId PEntity::getTimeout(uint8_t index)
{
  if (_entity)
  {
    return _entity->_timeComponent.getTimeout(index);
  }
  return 0;
}

int PEntity::getX()
{
  if (_entity)
  {
    return _entity->_bodyComponent->getPosition().x;
  }
  return 0;
}

int PEntity::getY()
{
  if (_entity)
  {
    return _entity->_bodyComponent->getPosition().y;
  }
  return 0;
}

Vect2 PEntity::getPosition()
{
  if (_entity)
  {
    return _entity->_bodyComponent->getPosition();
  }
  return Vect2(0, 0);
}
