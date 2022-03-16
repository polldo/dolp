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

bool PEntity::isMoving()
{
  if (_entity && _entity->_movementComponent)
  {
    auto mov = _entity->_movementComponent->getMovement();
    return (mov.x != 0 || mov.y != 0);
  }
  return false;
}

void PEntity::update(UpdateCallback onUpdate)
{
  if (_entity && _entity->_updateComponent)
    _entity->_updateComponent->config(onUpdate);
  else if (_entity)
    _entity->addUpdateComponent(onUpdate);
}

#if defined(MICROPYTHON)
void PEntity::update(mp_obj_t onUpdate)
{
  if (_entity && _entity->_updateComponent)
    _entity->_updateComponent->config(onUpdate);
  else if (_entity)
  {
    _entity->addUpdateComponent(NULL);
    _entity->_updateComponent->config(onUpdate);
  }
}

void PEntity::collision(mp_obj_t onCollision)
{
  if (_entity)
  {
    if (_entity->_collisionComponent == NULL)
      _entity->addCollisionComponent();
    _entity->_collisionComponent->configure(onCollision);
  }
}

#endif

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

void PEntity::setImage(const uint8_t *image, const uint8_t *mask)
{
  if (_entity)
  {
    _entity->_renderComponent->setImage(image, mask);
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

TimeoutId PEntity::newTimeout(uint8_t index)
{
  if (_entity)
  {
    return _entity->_timeComponent.init(index);
  }
  return 0;
}

TimeoutId PEntity::getTimeout(uint8_t index)
{
  if (_entity)
  {
    return _entity->_timeComponent.getTimeout(index);
  }
  return 0;
}

void PEntity::deleteTimeout(uint8_t index)
{
  if (_entity)
  {
    _entity->_timeComponent.deinit(index);
  }
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
