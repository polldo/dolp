#ifndef RENDER_COMPONENT_H
#define RENDER_COMPONENT_H

#include "Common.h"
#include "BodyComponent.h"

class Entity;

class RenderComponent {
  public:
    RenderComponent(Entity& entity);

    void render();
    //void update();

  private:
    Entity* _entity;
    BodyComponent* _body;
};

#endif 
