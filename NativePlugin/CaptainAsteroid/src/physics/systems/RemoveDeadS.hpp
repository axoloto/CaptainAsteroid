#pragma once

#include "entityx/System.h"

#include "entities/AsteroidField.hpp"
#include "entities/LaserShots.hpp"

namespace AsteroidsCPP
{
class RemoveDeadS : public entityx::System<RemoveDeadS>
{
public:
  RemoveDeadS(AsteroidField &asteroidField, LaserShots &laserShots);

  void update(entityx::EntityManager &entities,
    entityx::EventManager &events,
    double dt);

private:
  AsteroidField &m_asteroidField;
  LaserShots &m_laserShots;
};
}// namespace AsteroidsCPP