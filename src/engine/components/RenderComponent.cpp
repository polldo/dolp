#include "RenderComponent.h"
#include "engine/Entity.h"

#include "drivers/DriverLayer.h"

RenderComponent::RenderComponent() :
  _entity(NULL),
  _bodyComponent(NULL),
  _image(NULL)
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
  _image = NULL;
}

void RenderComponent::render()
{
  // select display driver and draw sprite
  Vect2& position = _bodyComponent->getPosition();
  Vect2& size = _bodyComponent->getSize();
  if (_image) display.drawImage(position.x, position.y, size.x, size.y, _image);
  else display.drawRectangle(position.x, position.y, size.x, size.y, WHITE_COLOR);
}

void RenderComponent::setImage(const uint8_t* image)
{
  _image = image;
}
