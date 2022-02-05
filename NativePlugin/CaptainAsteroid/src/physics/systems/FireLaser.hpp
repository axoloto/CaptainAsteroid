#pragma once

#include "entities/LaserShots.hpp"

#include "entityx/System.h"
#include "entityx/Event.h"

namespace CaptainAsteroidCPP
{
namespace Sys
{
  class FireLaser : public entityx::System<FireLaser>
  {
  public:
    FireLaser(EntityHelper::LaserShots &ls) : m_laserShots(ls){};

    void update(entityx::EntityManager &entities,
      entityx::EventManager &events,
      double dt);

  private:
    EntityHelper::LaserShots &m_laserShots;
  };
}// namespace Sys
}// namespace CaptainAsteroidCPP