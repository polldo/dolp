#include "Common.h"
#include "Entity.h"
#include "World.h"

int Entity::_classId = 0;

Entity::Entity() :
  _world(NULL),
  _bodyComponent(NULL),
  _renderComponent(NULL),
  _movementComponent(NULL)
{
}

Entity::~Entity()
{
}

void Entity::init(World* world)
{
  // Set Entity ID
  ++_classId;
  _id = _classId;
  // Set world
  _world = world;
  // Init components
  // At the moment this order is mandatory, because of how components are injected
  // (here body component is injected into render component at its initialization)
  addBodyComponent(); 
  addRenderComponent();
}

void Entity::deinit()
{
  // _world = NULL //useless. entities belong to only one world
  // Delete components
  if (_renderComponent) removeRenderComponent();
  if (_bodyComponent) removeBodyComponent();
  if (_movementComponent) removeMovementComponent();
}

void Entity::addBodyComponent()
{
  _bodyComponent = _world->newBodyComponent();
  _bodyComponent->init(this);
}

void Entity::addRenderComponent()
{
  _renderComponent = _world->newRenderComponent();
  //_renderComponent->init(this);
  _renderComponent->init(this, _bodyComponent);
}

void Entity::addMovementComponent()
{
  _movementComponent = _world->newMovementComponent();
  _movementComponent->init(this, _bodyComponent);
}

void Entity::removeBodyComponent()
{
  //if (_bodyComponent) { // Checked by the caller
  _bodyComponent->deinit();
  _world->deleteBodyComponent(_bodyComponent);
  _bodyComponent = NULL;
  //}
}

void Entity::removeRenderComponent()
{
  //if (_renderComponent) { // Checked by the caller
  _renderComponent->deinit();
  _world->deleteRenderComponent(_renderComponent);
  _renderComponent = NULL;
  //}
}

void Entity::removeMovementComponent()
{
  //if (_renderComponent) { // Checked by the caller  
  _movementComponent->deinit();
  _world->deleteMovementComponent(_movementComponent);
  _movementComponent = NULL;
  //}
}

BodyComponent* Entity::getBodyComponent()
{
  return _bodyComponent;
}

int Entity::getId()
{
  return _id;
}
