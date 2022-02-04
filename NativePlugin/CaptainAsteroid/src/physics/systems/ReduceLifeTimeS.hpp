#pragma once

#include "entityx/System.h"

#include "entities/LaserShots.hpp"

namespace AsteroidsCPP
{
class ReduceLifeTimeS : public entityx::System<ReduceLifeTimeS>
{
public:
  ReduceLifeTimeS(LaserShots &laserShots) : m_laserShots(laserShots){};

  void update(entityx::EntityManager &entities,
    entityx::EventManager &events,
    double dt);

private:
  LaserShots &m_laserShots;
};
}// namespace AsteroidsCPP