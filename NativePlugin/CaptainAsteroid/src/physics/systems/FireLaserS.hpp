#pragma once

#include "entities/LaserShots.hpp"

#include "entityx/System.h"
#include "entityx/Event.h"

namespace CaptainAsteroidCPP
{
class FireLaserS : public entityx::System<FireLaserS>
{
public:
  FireLaserS(LaserShots &ls) : m_laserShots(ls){};

  void update(entityx::EntityManager &entities,
    entityx::EventManager &events,
    double dt);

private:
  LaserShots &m_laserShots;
};
}// namespace CaptainAsteroidCPP