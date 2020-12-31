#include "World.h"

World::World()
{
}

World::~World()
{
}

void World::clear()
{
  // TODO
  // Clearing is not enough. They should be deinitialized
  // A possibility would be to move the init and deinit in each specific Pool
  // by overloading the newItem function of each specific pool 
  // (and passing the eventually needed init/deinit parameters)
  //_entities.clear();
  //_bodyComponents.clear();
  //_renderComponents.clear();
}

PEntity World::newEntity()
{
  Entity& entity = _entities.newItem();
  entity.init(this);
  return PEntity(entity);
}

void World::deleteEntity(PEntity pEntity)
{
  Entity& entity = *(pEntity._entity);
  entity.deinit();
  _entities.deleteItem(entity);
}

BodyComponent* World::newBodyComponent()
{
  return &_bodyComponents.newItem();
}

RenderComponent* World::newRenderComponent()
{
  return &_renderComponents.newItem();
}

MovementComponent* World::newMovementComponent()
{
  return &_movementComponents.newItem();
}

UpdateComponent* World::newUpdateComponent()
{
  return &_updateComponents.newItem();
}

IntStateComponent* World::newStateComponent()
{
  return &_stateComponents.newItem();
}

CollisionComponent* World::newCollisionComponent()
{
  return &_collisionComponents.newItem();
}

void World::deleteBodyComponent(BodyComponent* component)
{
  _bodyComponents.deleteItem(*component);
}

void World::deleteRenderComponent(RenderComponent* component)
{
  _renderComponents.deleteItem(*component);
}

void World::deleteMovementComponent(MovementComponent* component)
{
  _movementComponents.deleteItem(*component);
}

void World::deleteUpdateComponent(UpdateComponent* component)
{
  _updateComponents.deleteItem(*component);
}

void World::deleteStateComponent(IntStateComponent* component)
{
  _stateComponents.deleteItem(*component);
}

void World::deleteCollisionComponent(CollisionComponent* component)
{
  _collisionComponents.deleteItem(*component);
}

void World::update()
{
  _movementComponents.update();
  _bodyComponents.update();
  _collisionComponents.update();
  _updateComponents.update();
}

void World::render()
{
  _renderComponents.render();
}

