#pragma once

#include "entityx/System.h"

#include "entities/AsteroidField.hpp"
#include "entities/LaserShots.hpp"

namespace CaptainAsteroidCPP
{
namespace Sys
{
  class RemoveDead : public entityx::System<RemoveDead>
  {
  public:
    RemoveDead(EntityHelper::AsteroidField &asteroidField, EntityHelper::LaserShots &laserShots);

    void update(entityx::EntityManager &entities,
      entityx::EventManager &events,
      double dt);

  private:
    EntityHelper::AsteroidField &m_asteroidField;
    EntityHelper::LaserShots &m_laserShots;
  };
}// namespace Sys
}// namespace CaptainAsteroidCPP