#ifndef RENDER_COMPONENT_H
#define RENDER_COMPONENT_H

#ifndef RENDER_COMPONENTS_PER_WORLD
#define RENDER_COMPONENTS_PER_WORLD (200)
#endif

#include "Common.h"
#include "engine/Pool.h"
#include "BodyComponent.h"

class Entity;

class RenderComponent : public Poolable {
  public:
    RenderComponent();
    virtual ~RenderComponent();

    void render();
    //void update();

    void setImage(const uint8_t* image);

  protected:
    friend class Entity;
    void init(Entity* entity);
    void init(Entity* entity, BodyComponent* bodyComponent);
    void deinit();

  private:
    Entity* _entity;
    BodyComponent* _bodyComponent;
    const uint8_t* _image;
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
