#include "RenderComponent.h"
#include "engine/Entity.h"

#include "drivers/DriverLayer.h"

RenderComponent::RenderComponent(Entity& entity) :
  _entity(&entity)
{
  _body = _entity->getBody();
}

void RenderComponent::render()
{
  // select display driver and draw sprite
  Vect2& position = _body->getPosition();
  Vect2& size = _body->getSize();
  display.drawRectangle(position.x, position.y, size.x, size.y);
}
