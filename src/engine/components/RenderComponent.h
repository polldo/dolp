#ifndef RENDER_COMPONENT_H
#define RENDER_COMPONENT_H

#ifndef RENDER_COMPONENTS_PER_WORLD
#define RENDER_COMPONENTS_PER_WORLD (200)
#endif

#include "Common.h"
#include "engine/Pool.h"
#include "BodyComponent.h"
#include "drivers/Timer.h"

class Entity;

struct Animation {
  const uint8_t** images;
  const uint32_t* times;
  uint8_t length;

  Animation(const uint8_t** img, const uint32_t* tms, uint8_t len) : images(img), times(tms), length(len) {}
};

class RenderComponent : public Poolable {
  public:
    RenderComponent();
    virtual ~RenderComponent();

    void render();
    //void update();

    void setImage(const uint8_t* image);
    void setAnimation(const Animation& animation);
    void removeAnimation();

  protected:
    friend class Entity;
    void init(Entity* entity);
    void init(Entity* entity, BodyComponent* bodyComponent);
    void deinit();

  private:
    Entity* _entity;
    BodyComponent* _bodyComponent;

    const uint8_t* _image;
    const Animation* _animation;
    TimeoutId _animationTimeout;
    uint8_t _animationCounter;
};

class RenderComponentPool : public Pool<RenderComponent, RENDER_COMPONENTS_PER_WORLD> {
  public: 
    void render()
    {
#if defined (POOL_DOUBLE_LINK)
      auto component = getItems();
      while (component) {
        component->render();
        component = static_cast<RenderComponent*>(component->getNext());
      }
#else
      for (int i = 0; i < RENDER_COMPONENTS_PER_WORLD; i++) {
        if (_pool[i].isAllocated()) {
          _pool[i].render();
        }
      }
#endif
    }
};

#endif 
