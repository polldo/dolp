#ifndef UPDATE_COMPONENT_H
#define UPDATE_COMPONENT_H

#ifndef UPDATE_COMPONENTS_PER_WORLD
#define UPDATE_COMPONENTS_PER_WORLD (200)
#endif

#include "Common.h"
#include "engine/Pool.h"

class Entity;
class PEntity;

typedef void (*UpdateCallback)(PEntity entity);

class UpdateComponent : public Poolable {
  public:
    UpdateComponent();
    virtual ~UpdateComponent();

    void config(UpdateCallback callback);

  protected:
    friend class Entity;
    void init(Entity* entity, UpdateCallback callback);
    void deinit();

  private:
    friend class UpdateComponentPool;
    Entity* _entity;
    UpdateCallback _update;
};

class UpdateComponentPool : public Pool<UpdateComponent, UPDATE_COMPONENTS_PER_WORLD> {
  public: 
    void update();
};

#endif 
