#include "RenderComponent.h"
#include "engine/Entity.h"

#include "drivers/DriverLayer.h"

RenderComponent::RenderComponent() :
  _entity(NULL),
  _bodyComponent(NULL),
  _image(NULL),
  _animation(NULL)
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
  removeAnimation();
}

void RenderComponent::render()
{
  // select display driver and draw sprite
  Vect2& position = _bodyComponent->getPosition();
  Vect2& size = _bodyComponent->getSize();

  if (_animation) {
    if (timer.checkTimeout(_animationTimeout)) {
      timer.setTimeout(_animationTimeout, _animation->times[_animationCounter]);
      _image = _animation->images[_animationCounter];
      _animationCounter = (_animationCounter + 1) % _animation->length;
    }
  }

  if (_image) {
    display.drawImage(position.x, position.y, size.x, size.y, _image);

  } else {
    display.drawRectangle(position.x, position.y, size.x, size.y, WHITE_COLOR);
  }
}

void RenderComponent::setImage(const uint8_t* image)
{
  removeAnimation();
  _image = image;
}

void RenderComponent::setAnimation(const Animation& animation)
{
  _animation = &animation;
  _animationCounter = 0;
  _animationTimeout = timer.newTimeout(animation.times[0]);
  _image = animation.images[0];
}

void RenderComponent::removeAnimation()
{
  if (_animation) {
    _animation = NULL;
    timer.deleteTimeout(_animationTimeout);
  }
}
