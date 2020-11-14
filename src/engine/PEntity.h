#ifndef PENTITY_H
#define PENTITY_H

#include "Common.h"
#include "Entity.h"
#include "components/BodyComponent.h"
#include "components/RenderComponent.h"
#include "components/MovementComponent.h"

// just a reference to Entity
//typedef Entity& PEntity;

// Entity class is the storage of the entity
// PEntity is the interface that is retrieved to the user side application.

// Alternative to reference
class PEntity {
  public:
    virtual ~PEntity();
    PEntity();
    PEntity(Entity& entity);

    int getId();
    void configure(int x, int y, int width, int height);

    void moveTo(int x, int y, int speed);

    // alternatively
    //MovementComponent* getMovementComponent(); // search for component. if it doesn't exist, add it

  private:
    friend class World;
    Entity* _entity;
};

#endif // PENTITY_H
