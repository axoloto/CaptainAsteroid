#pragma once

#include <array>

#include "entityx/System.h"

namespace AsteroidsCPP
{
class AsteroidField
{
public:
  AsteroidField(entityx::EntityManager &entityManager) : m_entityManager(entityManager){};

  void init(int nbAsteroids = 10);
  std::array<float, 2> getCoords();

private:
  entityx::EntityManager &m_entityManager;

  int m_nbAsteroids;
};
}// namespace AsteroidsCPP
