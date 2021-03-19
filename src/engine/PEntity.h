#ifndef PENTITY_H
#define PENTITY_H

#include "Common.h"
#include "Entity.h"
#include "components/UpdateComponent.h"
#include "components/CollisionComponent.h"
#include "drivers/Timer.h"

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
    PEntity(Entity* entity);

    int getId();
    uint8_t getType();
    void setType(uint8_t entityType);
    void configure(int x, int y, int width, int height);

    void moveTo(int x, int y, int velocity);
    Vect2 getMovement();

    void update(UpdateCallback onUpdate);

    void collision();
    void collision(CollisionCallback onCollision);
    bool collided(PEntity other);

    int getState(uint8_t index);
    void setState(uint8_t index, int value);

    void setImage(const uint8_t* image);
    void setImage(const uint8_t* image, const uint8_t* mask);
    void setImage(const uint16_t* image);
    void setAnimation(const Animation& animation);

    void newTimeout(uint8_t index, uint64_t time);
    TimeoutId getTimeout(uint8_t index);
    bool checkTimeout(uint8_t index);

    Vect2 getPosition();
    int getX();
    int getY();

  private:
    friend class World;
    Entity* _entity;
};

#endif // PENTITY_H
