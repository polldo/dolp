#include "World.h"

World::World() :
  _entities(),
  _bodyComponents(),
  _renderComponents()
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

void World::deleteBodyComponent(BodyComponent* component)
{
  _bodyComponents.deleteItem(*component);
}

void World::deleteRenderComponent(RenderComponent* component)
{
  _renderComponents.deleteItem(*component);
}

void World::update()
{
}

void World::render()
{
  _renderComponents.render();
}

