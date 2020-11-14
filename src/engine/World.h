#ifndef WORLD_H
#define WORLD_H

#include "Entity.h"
#include "PEntity.h"
#include "components/BodyComponent.h"
#include "components/RenderComponent.h"

class World {
  public:
    World();
    virtual ~World();

    void clear();

    PEntity newEntity();
    void deleteEntity(PEntity entity);

    BodyComponent* newBodyComponent();
    RenderComponent* newRenderComponent();
    void deleteBodyComponent(BodyComponent* component);
    void deleteRenderComponent(RenderComponent* component);

    void update();
    void render();

  private:
    EntityPool _entities;
    BodyComponentPool _bodyComponents;
    RenderComponentPool _renderComponents;
};

#endif // WORLD_H
