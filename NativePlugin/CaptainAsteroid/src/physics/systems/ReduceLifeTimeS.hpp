#pragma once

#include "entityx/System.h"

namespace AsteroidsCPP
{
class ReduceLifeTimeS : public entityx::System<ReduceLifeTimeS>
{
public:
  ReduceLifeTimeS() = default;

  void update(entityx::EntityManager &entities,
    entityx::EventManager &events,
    double dt);
};
}// namespace AsteroidsCPP