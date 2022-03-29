#ifndef RENDER_COMPONENT_H
#define RENDER_COMPONENT_H

#ifndef RENDER_COMPONENTS_PER_WORLD
#define RENDER_COMPONENTS_PER_WORLD (200)
#endif

#include "Common.h"
#include "engine/Pool.h"
#include "BodyComponent.h"
#include "drivers/Timer.h"

#if defined(MICROPYTHON)
extern "C"
{
#include "py/runtime.h"
#include "py/obj.h"
}
#endif

class Entity;

// typedef uint16_t* ImageColor;
// typedef uint8_t* ImageMonochrome;

// Alternative for animation
//#ifdef ANIMATION_FRAME_ALTERNATIVE
// struct AnimationFrame {
// const uint8_t* image;
// const uint32_t duration;
//};
//#endif
// Example of the alternative:
// const uint8_t numberFrames = 2;
// const AnimationFrame monsterFrames[numberFrames] = { AnimationFrame(monsterImageOne, 100), AnimationFrame(monsterImageTwo, 200) };
// const Animation monsterAnimation(monsterFrames, numberFrames);

struct Animation
{
  // const AnimationFrame* frames;

#if defined(MICROPYTHON)
  const mp_obj_list_t *images;
  const mp_obj_list_t *masks;
  const mp_obj_list_t *times;

  Animation() : images(NULL), masks(NULL), times(NULL) {}
  Animation(const mp_obj_list_t *img, const mp_obj_list_t *tms, const mp_obj_list_t *msk) : images(img), masks(msk), times(tms) {}

  int upCount(const int count) const
  {
    return (count + 1) % images->len;
  }

  const uint8_t *image(const int count) const
  {
    mp_obj_t img = images->items[count];
    mp_buffer_info_t imgbuf;
    mp_get_buffer_raise(img, &imgbuf, 1);
    return (const uint8_t *)imgbuf.buf;
  }
  const int time(const int count) const
  {
    return mp_obj_get_int(times->items[count]);
  }
  const uint8_t *mask(const int count) const
  {
    mp_obj_t msk = masks->items[count];
    mp_buffer_info_t mskbuf;
    mp_get_buffer_raise(msk, &mskbuf, 1);
    return (const uint8_t *)mskbuf.buf;
  }
#else
  const uint8_t **imagesMonochrome;
  const uint8_t **imagesMonochromeMasks;
  const uint16_t **imagesColor;
  const uint32_t *times;
  uint8_t length;

  Animation() : imagesMonochrome(NULL), imagesMonochromeMasks(NULL), imagesColor(NULL), times(NULL), length(0) {}
  Animation(const uint8_t **img, const uint32_t *tms, uint8_t len) : imagesMonochrome(img), imagesMonochromeMasks(NULL), imagesColor(NULL), times(tms), length(len) {}
  Animation(const uint8_t **img, const uint8_t **msk, const uint32_t *tms, uint8_t len) : imagesMonochrome(img), imagesMonochromeMasks(msk), imagesColor(NULL), times(tms), length(len) {}
  Animation(const uint16_t **img, const uint32_t *tms, uint8_t len) : imagesMonochrome(NULL), imagesMonochromeMasks(NULL), imagesColor(img), times(tms), length(len) {}
#endif
};

class RenderComponent : public Poolable
{
public:
  RenderComponent();
  virtual ~RenderComponent();

  void render();
  // void update();
  void updateAnimation();

  void setImage(const uint8_t *image);
  void setImage(const uint8_t *image, const uint8_t *mask);
  void setImage(const uint16_t *image);
  void setAnimation(const Animation &animation);
  void removeAnimation();

protected:
  friend class Entity;
  void init(Entity *entity);
  void init(Entity *entity, BodyComponent *bodyComponent);
  void deinit();

private:
  Entity *_entity;
  BodyComponent *_bodyComponent;

  const uint8_t *_imageMonochrome;
  const uint8_t *_imageMonochromeMask;
  const uint16_t *_imageColor;
  const Animation *_animation;
  TimeoutId _animationTimeout;
  uint8_t _animationCounter;
};

class RenderComponentPool : public Pool<RenderComponent, RENDER_COMPONENTS_PER_WORLD>
{
public:
  void render()
  {
#if defined(POOL_DOUBLE_LINK)
    auto component = getItems();
    while (component)
    {
      component->render();
      component = static_cast<RenderComponent *>(component->getNext());
    }
#else
    for (int i = 0; i < RENDER_COMPONENTS_PER_WORLD; i++)
    {
      if (_pool[i].isAllocated())
      {
        _pool[i].render();
      }
    }
#endif
  }
};

#endif
