#include "BodyComponent.h"
#include "engine/Entity.h"

//#define HITBOX_MARGIN (1)

BodyComponent::BodyComponent() : _entity(NULL)
{
}

BodyComponent::~BodyComponent()
{
}

void BodyComponent::init(Entity *entity)
{
  _entity = entity;
  _position = Vect2(0, 0);
  _size = Vect2(0, 0);
}

void BodyComponent::init(Entity *entity, int x, int y, int w, int h)
{
  _entity = entity;
  _position = Vect2(x, y);
  _size = Vect2(w, h);
#if defined(HITBOX_MARGIN)
  _minHitbox = Vect2((x - w / 2 * HITBOX_MARGIN), (y - h / 2 * HITBOX_MARGIN));
  _maxHitbox = Vect2((x + w / 2 * HITBOX_MARGIN), (y + h / 2 * HITBOX_MARGIN));
#else
  _minHitbox = Vect2((x - w / 2), (y - h / 2));
  _maxHitbox = Vect2((x + w / 2), (y + h / 2));
#endif
}

void BodyComponent::deinit()
{
  _entity = NULL;
}

void BodyComponent::configure(int x, int y, int width, int height)
{
  _position.set(x, y);
  _size.set(width, height);
#if defined(HITBOX_MARGIN)
  _minHitbox.set((x - width / 2 * HITBOX_MARGIN), (y - height / 2 * HITBOX_MARGIN));
  _maxHitbox.set((x + width / 2 * HITBOX_MARGIN), (y + height / 2 * HITBOX_MARGIN));
#else
  _minHitbox.set((x - width / 2), (y - height / 2));
  _maxHitbox.set((x + width / 2), (y + height / 2));
#endif
}

void BodyComponent::update()
{
#if defined(HITBOX_MARGIN)
  _minHitbox.set(_position.x - _size.x / 2 * HITBOX_MARGIN, _position.y - _size.y / 2 * HITBOX_MARGIN);
  _maxHitbox.set(_position.x + _size.x / 2 * HITBOX_MARGIN, _position.y + _size.y / 2 * HITBOX_MARGIN);
#else
  _minHitbox.set((_position.x - _size.x / 2), (_position.y - _size.y / 2));
  _maxHitbox.set((_position.x + _size.x / 2), (_position.y + _size.y / 2));
#endif
}

Vect2 &BodyComponent::getPosition()
{
  return _position;
}

Vect2 &BodyComponent::getSize()
{
  return _size;
}

Vect2 &BodyComponent::getMaxHitbox()
{
  return _maxHitbox;
}

Vect2 &BodyComponent::getMinHitbox()
{
  return _minHitbox;
}
