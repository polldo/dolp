#ifndef STATE_COMPONENT_H
#define STATE_COMPONENT_H

#ifndef STATE_COMPONENTS_PER_WORLD
#define STATE_COMPONENTS_PER_WORLD (200)
#endif

#ifndef STATES_FOR_ENTITY
#define STATES_FOR_ENTITY (4)
#endif

#include "Common.h"
#include "engine/Pool.h"

// API functions: monster.getState(MONSTER_LIFE), where an enum MONSTER_STATE() lists 
// indexes of state variables 

// This component should be templated with some macros to ensure more freedom
// Or provide multiple already defined state components 

class Entity;

template <class T, int N>
class StateComponent : public Poolable {
  public:
    StateComponent() : _entity(NULL) {}
    virtual ~StateComponent() {}

    T getState(uint8_t index)
    {
      // if (index >= STATES_FOR_ENTITY) { //out of bound }
      return _state[index];
    }

    void setState(uint8_t index, T value)
    {
      _state[index] = value;
    }

  protected:
    friend class Entity;
    void init(Entity* entity) { _entity = entity; }
    void deinit() { _entity = NULL; }

  private:
    Entity* _entity;
    T _state[N];
};

//class IntStateComponentPool : public Pool<StateComponent<int, STATES_FOR_ENTITY>, STATE_COMPONENTS_PER_WORLD> {
typedef StateComponent<int, STATES_FOR_ENTITY> IntStateComponent;
class IntStateComponentPool : public Pool<IntStateComponent, STATE_COMPONENTS_PER_WORLD> {
  public: 
    void update() {}
};


#endif 
