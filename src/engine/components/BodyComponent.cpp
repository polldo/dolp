#include "BodyComponent.h"
#include "engine/Entity.h"

BodyComponent::BodyComponent() :
  _entity(NULL)
{
}

BodyComponent::~BodyComponent() 
{
}

void BodyComponent::init(Entity* entity)
{
  _entity = entity;
  _position = Vect2(0, 0);
  _size = Vect2(0, 0);
}

void BodyComponent::init(Entity* entity, int x, int y, int w, int h)
{
  _entity = entity;
  _position = Vect2(x, y);
  _size = Vect2(w, h);
}

void BodyComponent::deinit()
{
  _entity = NULL;
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
