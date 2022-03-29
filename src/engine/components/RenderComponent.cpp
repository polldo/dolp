#include "RenderComponent.h"
#include "engine/Entity.h"

#include "drivers/DriverLayer.h"

RenderComponent::RenderComponent() : _entity(NULL),
                                     _bodyComponent(NULL),
                                     _imageMonochrome(NULL),
                                     _imageMonochromeMask(NULL),
                                     _imageColor(NULL),
                                     _animation(NULL)
{
}

RenderComponent::~RenderComponent()
{
}

void RenderComponent::init(Entity *entity)
{
  _entity = entity;
  _bodyComponent = _entity->getBodyComponent();
}

void RenderComponent::init(Entity *entity, BodyComponent *bodyComponent)
{
  _entity = entity;
  _bodyComponent = bodyComponent;
  _imageMonochrome = NULL;
  _imageMonochromeMask = NULL;
  _imageColor = NULL;
  _animation = NULL;
}

void RenderComponent::deinit()
{
  _entity = NULL;
  _bodyComponent = NULL;
  _imageMonochrome = NULL;
  _imageMonochromeMask = NULL;
  _imageColor = NULL;
  removeAnimation();
}

void RenderComponent::render()
{
  // select display driver and draw sprite
  Vect2 &position = _bodyComponent->getPosition();
  Vect2 &size = _bodyComponent->getSize();

  if (_animation)
  {
    if (timer.checkTimeout(_animationTimeout))
    {
      updateAnimation();
    }
  }

  if (_imageMonochrome && _imageMonochromeMask)
  {
    display.drawImage(position.x, position.y, size.x, size.y, _imageMonochrome, _imageMonochromeMask);
  }
  else if (_imageMonochrome)
  {
    display.drawImage(position.x, position.y, size.x, size.y, _imageMonochrome);
  }
  else if (_imageColor)
  {
    display.drawImage(position.x, position.y, size.x, size.y, _imageColor);
  }
  else
  {
    display.drawRectangle(position.x, position.y, size.x, size.y, WHITE_COLOR);
  }
}

void RenderComponent::updateAnimation()
{
#if defined(MICROPYTHON)
  timer.setTimeout(_animationTimeout, _animation->time(_animationCounter), false);
  _imageMonochrome = _animation->image(_animationCounter);
  if (_animation->masks)
  {
    _imageMonochromeMask = _animation->mask(_animationCounter);
  }
  _animationCounter = _animation->upCount(_animationCounter);
#else
  timer.setTimeout(_animationTimeout, _animation->times[_animationCounter], false);
  if (_animation->imagesMonochrome && _animation->imagesMonochromeMasks)
  {
    _imageMonochrome = _animation->imagesMonochrome[_animationCounter];
    _imageMonochromeMask = _animation->imagesMonochromeMasks[_animationCounter];
  }
  else if (_animation->imagesMonochrome)
  {
    _imageMonochrome = _animation->imagesMonochrome[_animationCounter];
  }
  else if (_animation->imagesColor)
  {
    _imageColor = _animation->imagesColor[_animationCounter];
  }
  _animationCounter = (_animationCounter + 1) % _animation->length;
#endif
}

void RenderComponent::setImage(const uint8_t *image)
{
  removeAnimation();
  _imageMonochrome = image;
  _imageMonochromeMask = NULL;
  _imageColor = NULL;
}

void RenderComponent::setImage(const uint8_t *image, const uint8_t *mask)
{
  removeAnimation();
  _imageMonochrome = image;
  _imageMonochromeMask = mask;
  _imageColor = NULL;
}

void RenderComponent::setImage(const uint16_t *image)
{
  removeAnimation();
  _imageColor = image;
  _imageMonochrome = NULL;
  _imageMonochromeMask = NULL;
}

void RenderComponent::setAnimation(const Animation &animation)
{
#if defined(MICROPYTHON)
  _animation = &animation;
  _animationTimeout = timer.newTimeout();
  _imageMonochrome = NULL;
  _imageMonochromeMask = NULL;
  _imageColor = NULL;
  updateAnimation();
#else
  _animation = &animation;
  _animationCounter = 1;
  _animationTimeout = timer.newTimeout();
  timer.setTimeout(_animationTimeout, animation.times[0], false);

  if (animation.imagesMonochrome && animation.imagesMonochromeMasks)
  {
    _imageMonochrome = animation.imagesMonochrome[0];
    _imageMonochromeMask = animation.imagesMonochromeMasks[0];
    _imageColor = NULL;
  }
  else if (animation.imagesMonochrome)
  {
    _imageMonochrome = animation.imagesMonochrome[0];
    _imageMonochromeMask = NULL;
    _imageColor = NULL;
  }
  else if (animation.imagesColor)
  {
    _imageColor = animation.imagesColor[0];
    _imageMonochrome = NULL;
    _imageMonochromeMask = NULL;
  }
#endif
}

void RenderComponent::removeAnimation()
{
  if (_animation)
  {
    _animation = NULL;
    timer.deleteTimeout(_animationTimeout);
  }
}
