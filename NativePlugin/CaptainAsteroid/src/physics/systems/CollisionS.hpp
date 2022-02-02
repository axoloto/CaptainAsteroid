#pragma once

#include "entityx/System.h"

namespace AsteroidsCPP
{
class CollisionS : public entityx::System<CollisionS>
{
public:
  CollisionS();

  void update(entityx::EntityManager &entities,
    entityx::EventManager &events,
    double dt);

private:
};
}// namespace AsteroidsCPP