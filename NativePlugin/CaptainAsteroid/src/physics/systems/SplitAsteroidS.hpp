#pragma once

#include "entityx/System.h"

#include "entities/AsteroidField.hpp"

namespace CaptainAsteroidCPP
{
class SplitAsteroidS : public entityx::System<SplitAsteroidS>
{
public:
  SplitAsteroidS(AsteroidField &asteroidField);

  void update(entityx::EntityManager &entities,
    entityx::EventManager &events,
    double dt);

private:
  AsteroidField &m_asteroidField;
};
}// namespace CaptainAsteroidCPP