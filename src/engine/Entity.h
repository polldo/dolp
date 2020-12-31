#ifndef ENTITY_H
#define ENTITY_H

#ifndef ENTITIES_PER_WORLD
#define ENTITIES_PER_WORLD (200)
#endif

#include "Common.h"
#include "Pool.h"
#include "components/BodyComponent.h"
#include "components/RenderComponent.h"
#include "components/MovementComponent.h"
#include "components/UpdateComponent.h"
#include "components/StateComponent.h"
#include "components/CollisionComponent.h"

// Entity class should not be extended because their life cycle is managed by the engine.
// To add specific features, components must be used -> give users components to model their entities.

// Other possible components
// STATE COMPONENT
// COLLISION COMPONENT
// UPDATE COMPONENT 

class PEntity;

// class Entity 
  // is the internal Entity class (the storage, containing pointers to components).
  // Its life cycle is managed by the World it lives in, allocated in a pool.
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
    virtual ~Entity();

    void addBodyComponent();
    void addRenderComponent();
    void addMovementComponent();
    void addUpdateComponent(UpdateCallback onUpdate);
    void addStateComponent();
    void addCollisionComponent();

    void removeBodyComponent();
    void removeRenderComponent();
    void removeMovementComponent();
    void removeUpdateComponent();
    void removeStateComponent();
    void removeCollisionComponent();

    BodyComponent* getBodyComponent();
    //RenderComponent* getRenderComponent();

    // These way of handling components is generic but CPU expensive
    // because an array of components should be traversed. still, it would be a possibility
    //void addComponent(BaseComponent* component);
    //void removeComponent(BaseComponent* component);
    //Component getComponent(uint8_t componentId);
    //BaseComponent* _components[COMPONENTS_PER_ENTITY];
    //int _componentsSize;

    // static Entity* create(); //Alternative creation method.. but it needs to know the world anyway

  public:
    // Use the ID to check entities equality
    int getId();

  protected:
    friend class World;
    void init(World* world);
    void deinit();

  private:
    friend class PEntity;
    static int _classId;
    int _id;

    // Component pools for each type of components. The size for each pool should be user-specified (default size to be decided)
    // The pools should be defined in World class.
    // Then, here there should be an array of pointers to Component which will be used to iterate all entity's components.
    // When an entity gets destroyed, its components should be destroyed too.

    World* _world;
    BodyComponent* _bodyComponent;
    RenderComponent* _renderComponent;
    MovementComponent* _movementComponent;
    UpdateComponent* _updateComponent;
    IntStateComponent* _stateComponent;
    CollisionComponent* _collisionComponent;
};

// Alternative to component POOLS
// create a container for each component type. the container is an array of fixed size that takes the initialized elements at the head 
// of the array. to do this, new elements are initialized one after the other, when an element is eliminated it gets swapped with the 
// latest initialized element of the array. When there is a SWAP operation, the entity of the swapped component should update 
// its pointer to the component. to do this, the component should be recognizable from the entity (some unique id is needed) OR it
// the component could change the pointer itself. The latter can be done by using an object that points to the component and is pointed
// to by the component. (class ComponentPointer)

class EntityPool : public Pool<Entity, ENTITIES_PER_WORLD> {
  public: 
    void update()
    {
      for (int i = 0; i < ENTITIES_PER_WORLD; i++) {
        if (_pool[i].isAllocated()) {
          //_pool[i].update();
        }
      }
    }
};

#endif // ENTITY_H
