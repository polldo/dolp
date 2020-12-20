#include "RenderComponent.h"
#include "engine/Entity.h"

#include "drivers/DriverLayer.h"

RenderComponent::RenderComponent() :
  _entity(NULL),
  _bodyComponent(NULL)
{
}

RenderComponent::~RenderComponent() 
{
}

void RenderComponent::init(Entity* entity)
{
  _entity = entity;
  _bodyComponent = _entity->getBodyComponent();
}

void RenderComponent::init(Entity* entity, BodyComponent* bodyComponent)
{
  _entity = entity;
  _bodyComponent = bodyComponent;
}

void RenderComponent::deinit()
{
  _entity = NULL;
  _bodyComponent = NULL;
}

void RenderComponent::render()
{
  // select display driver and draw sprite
  Vect2& position = _bodyComponent->getPosition();
  Vect2& size = _bodyComponent->getSize();
  display.drawRectangle(position.x, position.y, size.x, size.y, WHITE_COLOR);
}
