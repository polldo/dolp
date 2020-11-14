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

  protected:
    friend class Entity;
    void init(Entity* entity);
    void init(Entity* entity, BodyComponent* bodyComponent);
    void deinit();

  private:
    Entity* _entity;
    BodyComponent* _bodyComponent;
};

class RenderComponentPool : public Pool<RenderComponent, RENDER_COMPONENTS_PER_WORLD> {
  public: 
    void render()
    {
      for (int i = 0; i < RENDER_COMPONENTS_PER_WORLD; i++) {
        if (_pool[i].isAllocated()) {
          _pool[i].render();
        }
      }
      // Alternative
      //auto component = _headAllocated;
      //while (component) {
        //component->render();
        //component = component->getNext();
      //}
    }
};

#endif 
