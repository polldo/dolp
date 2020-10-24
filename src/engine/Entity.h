#ifndef ENTITY_H
#define ENTITY_H

#ifndef ENTITIES_PER_WORLD
#define ENTITIES_PER_WORLD (200)
#endif

#include "Common.h"
#include "Pool.h"
#include "Body.h" 
#include "components/BodyComponent.h"
#include "components/RenderComponent.h"

typedef Entity& PEntity;

// Alternative to reference
//class PEntity {

  //private:
    //Entity* _entity;
//};

class World;

class Entity : public Poolable {
  // Protect constructor ?
  //protected:
    //friend class Pool<Entity, ENTITIES_PER_WORLD>;
    //friend class EntityPool;
  public:
    Entity();
    Entity(World* world);
    virtual ~Entity();

  protected:
    friend class World;
    void init(World* world);

  public:
    int getId();
    void configure(int x, int y, int width, int height);
    BodyComponent* getBody();
    void render();

  private:
    static int _classId;
    int _id;

    World* _world;
    BodyComponent _body;
    RenderComponent _renderer;
};

class EntityPool : public Pool<Entity, ENTITIES_PER_WORLD> {
  public: 
    void render()
    {
      for (int i = 0; i < ENTITIES_PER_WORLD; i++) {
        _pool[i].render();
      }
    }
};

#endif // ENTITY_H
