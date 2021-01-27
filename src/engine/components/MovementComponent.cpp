#include "MovementComponent.h"
#include "engine/Entity.h"
#include <math.h>

#define DECIMAL_SAVE 1024 // needed to avoid using float while preserving decimal digits
#define VELOCITY_RATE 8

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
  _movement = Vect2(0, 0);
}

void MovementComponent::init(Entity* entity, BodyComponent* bodyComponent)
{
  _entity = entity;
  _bodyComponent = bodyComponent;
  _movement = Vect2(0, 0);
}

void MovementComponent::deinit()
{
  _entity = NULL;
  _bodyComponent = NULL;
  _movement = Vect2(0, 0);
}

void MovementComponent::configure(int x, int y, int velocity)
{
  configure(Vect2(x, y), velocity);
}

void MovementComponent::configure(Vect2 destination, int velocity)
{
  if (velocity == 0) {
    _movement = Vect2(0, 0);
    return;
  }

  // vectorial operators could be implemented and used
  Vect2& currentPosition = _bodyComponent->getPosition();
  float distanceX = destination.x - currentPosition.x;
  float distanceY = destination.y - currentPosition.y;
  float len = sqrt(distanceX * distanceX + distanceY * distanceY);

  if ((int)len == 0) {
    _movement = Vect2(0, 0);
    return;
  }

  _movement = Vect2(distanceX * velocity * DECIMAL_SAVE / VELOCITY_RATE / len, 
                    distanceY * velocity * DECIMAL_SAVE / VELOCITY_RATE / len);

  _movedX = currentPosition.x * DECIMAL_SAVE;
  _movedY = currentPosition.y * DECIMAL_SAVE;

  _destination = destination; 
}

void MovementComponent::update() 
{
  if (_movement.x == 0 && _movement.y == 0) { 
    return; 
  }

  Vect2& position = _bodyComponent->getPosition();
  // in this way movement is cleared in the frame following the last position update
  if (position.x == _destination.x && position.y == _destination.y) {
    _movement = Vect2(0, 0);
    return;
  } 

  int nextX = (_movedX + _movement.x) / DECIMAL_SAVE;
  if ( (_movement.x > 0 && nextX >= _destination.x) || (_movement.x < 0 && nextX <= _destination.x) ) {
    _movedX = _destination.x * DECIMAL_SAVE;
    // uncommenting this will result in clearing movement in the same cycle of the last position update
    //_movement.x = 0; 
  } else {
    _movedX += _movement.x;
  }

  int nextY = (_movedY + _movement.y) / DECIMAL_SAVE;
  if ( (_movement.y > 0 && nextY >= _destination.y) || (_movement.y < 0 && nextY <= _destination.y) ) {
    _movedY = _destination.y * DECIMAL_SAVE;
    // uncommenting this will result in clearing movement in the same cycle of the last position update
    //_movement.y = 0;
  } else {
    _movedY += _movement.y;
  }

  position.set(_movedX / DECIMAL_SAVE, _movedY / DECIMAL_SAVE);
}

Vect2& MovementComponent::getMovement()
{
  return _movement;
}
