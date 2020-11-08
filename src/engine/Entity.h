#ifndef ENTITY_H
#define ENTITY_H

#ifndef ENTITIES_PER_WORLD
#define ENTITIES_PER_WORLD (200)
#endif

#include "Common.h"
#include "Pool.h"
#include "components/BodyComponent.h"
#include "components/RenderComponent.h"

// Entity class should not be extended because to add specific features 
// components must be used. -> give users a flexible way to add/retrieve components.
// also the number of components per entity should be overwritten. some entities will not need at all components, some other 
// will need many components. By using Templates?

// UPDATE COMPONENT 
// it could the most used component, it probably will need to access
// the other components. Its behavior should be implemented by the user. How? Extended component class? callback?

class PEntity;

// class Entity 
  // is the internal Entity class (the storage, containing pointers to components and directly defining some components)
  // the user will use class PEntity that will contain only the pointer to the attached Entity (internal one)
  // and the functions to access it

class World;

class Entity : public Poolable {
  // Protect constructor ? this class should not be used by users. that's the purpose of PEntity
  //protected:
    //friend class Pool<Entity, ENTITIES_PER_WORLD>;
    //friend class EntityPool;
  public:
    Entity();
    Entity(World* world);
    virtual ~Entity();

    // static Entity* create(); //Alternative creation method.. but it needs to know the world anyway

  protected:
    friend class World;
    void init(World* world);
    void deinit();

  public:
    int getId();
    void configure(int x, int y, int width, int height);
    BodyComponent* getBody();
    void render();

    //Component getComponent(uint8_t componentId);

  private:
    friend class PEntity;
    static int _classId;
    int _id;

    // Component pools for each type of components. The size for each pool should be user-specified (default size to be decided)
    // The pools should be defined in World class.
    // Then, here there should be an array of pointers to Component which will be used to iterate all entity's components.
    // When an entity gets destroyed, its components should be destroyed too.
    //
    // Components should have type IDs, indicating the TYPE of the component
    //
    // Implement by default many components that could be useful -> for instance 'LifeComponent'
    // and then just ask the user to set the size of the pool for such component at compile time

    World* _world;
    // here are the frequently used components (i.e. frequently accessed by entity.getComponent())
    // ..to avoid searching for them in the array of components
    // Users could add/remove them from here
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
