#pragma once

#include "entityx/System.h"

class CollisionS : public entityx::System<CollisionS>
{
public:
  CollisionS();

  void update(entityx::EntityManager &entities,
    entityx::EventManager &events,
    double dt);

private:
};