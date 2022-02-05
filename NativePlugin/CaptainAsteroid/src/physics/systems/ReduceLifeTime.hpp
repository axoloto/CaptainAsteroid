#pragma once

#include "entityx/System.h"

namespace CaptainAsteroidCPP
{
namespace Sys
{
  class ReduceLifeTime : public entityx::System<ReduceLifeTime>
  {
  public:
    ReduceLifeTime() = default;

    void update(entityx::EntityManager &entities,
      entityx::EventManager &events,
      double dt);
  };
}// namespace Sys
}// namespace CaptainAsteroidCPP