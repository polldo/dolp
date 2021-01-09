#include "MovementComponent.h"
#include "engine/Entity.h"
#include <math.h>

MovementComponent::MovementComponent() :
  _entity(NULL),
  _bodyComponent(NULL)
{
}

MovementComponent::~MovementComponent()
{
}

void MovementComponent::init(Entity* entity)
{
  _entity = entity;
  _bodyComponent = _entity->getBodyComponent();
}

void MovementComponent::init(Entity* entity, BodyComponent* bodyComponent)
{
  _entity = entity;
  _bodyComponent = bodyComponent;
}

void MovementComponent::deinit()
{
  _entity = NULL;
  _bodyComponent = NULL;
}

void MovementComponent::configure(int x, int y, int speed)
{
  configure(Vect2(x, y), speed);
}

// Just a sample ! To be implemented
void MovementComponent::configure(Vect2 destination, int speed)
{
  // vectorial operators could be implemented and used
  Vect2& currentPosition = _bodyComponent->getPosition();
  int directionX = (destination.x >= currentPosition.x) ? 1 : -1;
  int directionY = (destination.y >= currentPosition.y) ? 1 : -1;
  _destination = destination; 
  _direction = Vect2(directionX, directionY);
  _dS = speed;
}

// Just a sample ! To be implemented
void MovementComponent::update() 
{
  Vect2& position = _bodyComponent->getPosition();
  int dX = abs(position.x - _destination.x);
  if (_dS < dX) dX = _dS;
  int dY = abs(position.y - _destination.y);
  if (_dS < dY) dY = _dS;
  position.set( position.x + (_direction.x * dX), 
                position.y + (_direction.y * dY));
}
