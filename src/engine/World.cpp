#include "World.h"

World::World() :
  _entities()
{
}

World::~World()
{
}

void World::clear()
{
  _entities.clear();
}

PEntity World::newEntity()
{
  PEntity entity = _entities.newItem();
  entity.init(this);
  return entity;
}

void World::deleteEntity(PEntity entity)
{
  _entities.deleteItem(entity);
}

//void World::update()
//void World::update()
//{
  //for (int i = 0; i < _movementsSize; i++) {
      //_movements[i].update();
  //}
//}

void World::render()
{
  _entities.render();
}

