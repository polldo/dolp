#ifndef WORLD_H
#define WORLD_H

#include "Entity.h"
#include "PEntity.h"
#include "components/BodyComponent.h"
#include "components/MovementComponent.h"
#include "components/RenderComponent.h"
#include "components/UpdateComponent.h"
#include "components/StateComponent.h"
#include "components/CollisionComponent.h"

class World
{
public:
  World();
  virtual ~World();

  void clear();

  PEntity newEntity();
  void deleteEntity(PEntity entity);

  BodyComponent *newBodyComponent();
  RenderComponent *newRenderComponent();
  MovementComponent *newMovementComponent();
  UpdateComponent *newUpdateComponent();
  IntStateComponent *newStateComponent();
  CollisionComponent *newCollisionComponent();

  void deleteBodyComponent(BodyComponent *component);
  void deleteRenderComponent(RenderComponent *component);
  void deleteMovementComponent(MovementComponent *component);
  void deleteUpdateComponent(UpdateComponent *component);
  void deleteStateComponent(IntStateComponent *component);
  void deleteCollisionComponent(CollisionComponent *component);

  void update();
  void render();

private:
  EntityPool _entities;
  BodyComponentPool _bodyComponents;
  RenderComponentPool _renderComponents;
  MovementComponentPool _movementComponents;
  UpdateComponentPool _updateComponents;
  IntStateComponentPool _stateComponents;
  CollisionComponentPool _collisionComponents;
};

#endif // WORLD_H
