#include "Common.h"
#include "Entity.h"

int Entity::_classId = 0;

Entity::Entity() :
  _world(NULL),
  _body(*this),
  _renderer(*this)
{
}

Entity::Entity(World* world) :
  _world(world),
  _body(*this),
  _renderer(*this)
{
}

Entity::~Entity()
{
}

void Entity::init(World* world)
{
  _world = world;
  ++_classId;
  _id = _classId;
  // clean entity state
  //_body.init();
  //_renderer.init();
}

void Entity::deinit()
{
  // delete all components
  //_body.deinit()
  //_body.configure(0, 0, 0, 0);
}

void Entity::configure(int x, int y, int width, int height)
{
  _body.configure(x, y, width, height);
}

int Entity::getId()
{
  return _id;
}

void Entity::render()
{
  _renderer.render();
}

BodyComponent* Entity::getBody()
{
  return &_body;
}
