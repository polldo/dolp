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
  _velocity = Vect2(0, 0);
}

void MovementComponent::configure(int x, int y, int velocity)
{
  configure(Vect2(x, y), Vect2(velocity, velocity));
}

void MovementComponent::configure(int x, int y, int vx, int vy)
{
  configure(Vect2(x, y), Vect2(vx, vy));
}

// Just a sample ! To be implemented
void MovementComponent::configure(Vect2 destination, Vect2 velocity)
{
  // vectorial operators could be implemented and used
  Vect2& currentPosition = _bodyComponent->getPosition();
  int directionX = (destination.x >= currentPosition.x) ? 1 : -1;
  int directionY = (destination.y >= currentPosition.y) ? 1 : -1;
  _destination = destination; 
  _direction = Vect2(directionX, directionY);
  _velocity = velocity;
}

// Just a sample ! To be implemented
void MovementComponent::update() 
{
  if (_velocity.x == 0 && _velocity.y == 0) { 
    return; 
  }
  Vect2& position = _bodyComponent->getPosition();
  if (position.x == _destination.x && position.y == _destination.y) {
    _velocity = Vect2(0, 0);
  } else {
    int dX = abs(position.x - _destination.x);
    if (_velocity.x < dX) dX = _velocity.x;
    int dY = abs(position.y - _destination.y);
    if (_velocity.y < dY) dY = _velocity.y;
    position.set( position.x + (_direction.x * dX), 
                  position.y + (_direction.y * dY));
  }
}

Vect2& MovementComponent::getVelocity()
{
  return _velocity;
}
