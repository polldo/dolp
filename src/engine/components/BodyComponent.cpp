#include "BodyComponent.h"
#include "engine/Entity.h"

BodyComponent::BodyComponent(Entity& entity) :
  _position(0, 0),
  _size(0, 0)
{
  _entity = &entity;
}

void BodyComponent::configure(int x, int y, int width, int height)
{
  _position.set(x, y);
  _size.set(width, height);
}

Vect2& BodyComponent::getPosition()
{
  return _position;
}

Vect2& BodyComponent::getSize()
{
  return _size;
}
