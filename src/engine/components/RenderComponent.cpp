#include "RenderComponent.h"
#include "engine/Entity.h"

#include "drivers/DriverLayer.h"

RenderComponent::RenderComponent() :
  _entity(NULL),
  _bodyComponent(NULL),
  _imageMonochrome(NULL),
  _imageColor(NULL),
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
  _imageMonochrome = NULL;
  _imageColor = NULL;
  _animation = NULL;
}

void RenderComponent::deinit()
{
  _entity = NULL;
  _bodyComponent = NULL;
  _imageMonochrome = NULL;
  _imageColor = NULL;
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
      if (_animation->imagesMonochrome) _imageMonochrome = _animation->imagesMonochrome[_animationCounter];
      else if (_animation->imagesColor) _imageColor = _animation->imagesColor[_animationCounter];
      _animationCounter = (_animationCounter + 1) % _animation->length;
    }
  }

  if (_imageMonochrome) {
    display.drawImage(position.x, position.y, size.x, size.y, _imageMonochrome);

  } else if (_imageColor) {
    display.drawImage(position.x, position.y, size.x, size.y, _imageColor);

  } else {
    display.drawRectangle(position.x, position.y, size.x, size.y, WHITE_COLOR);
  }
}

void RenderComponent::setImage(const uint8_t* image)
{
  removeAnimation();
  _imageMonochrome = image;
  _imageColor = NULL;
}

void RenderComponent::setImage(const uint16_t* image)
{
  removeAnimation();
  _imageColor = image;
  _imageMonochrome = NULL;
}

void RenderComponent::setAnimation(const Animation& animation)
{
  _animation = &animation;
  _animationCounter = 1;
  _animationTimeout = timer.newTimeout(animation.times[0]);
  if (animation.imagesColor) {
    _imageColor = animation.imagesColor[0];
    _imageMonochrome = NULL;
  }
  else if (animation.imagesMonochrome) {
    _imageMonochrome = animation.imagesMonochrome[0];
    _imageColor = NULL;
  }
}

void RenderComponent::removeAnimation()
{
  if (_animation) {
    _animation = NULL;
    timer.deleteTimeout(_animationTimeout);
  }
}
