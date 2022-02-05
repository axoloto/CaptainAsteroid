#pragma once

#include "entityx/System.h"

#include "entities/AsteroidField.hpp"

namespace CaptainAsteroidCPP
{
namespace Sys
{
  class SplitAsteroid : public entityx::System<SplitAsteroid>
  {
  public:
    SplitAsteroid(EntityHelper::AsteroidField &asteroidField);

    void update(entityx::EntityManager &entities,
      entityx::EventManager &events,
      double dt);

  private:
    EntityHelper::AsteroidField &m_asteroidField;
  };
}// namespace Sys
}// namespace CaptainAsteroidCPP