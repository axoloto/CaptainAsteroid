#pragma once

#include <array>

#include "utils.hpp"

#include "entityx/System.h"

namespace AsteroidsCPP
{
class AsteroidField
{
public:
  AsteroidField(entityx::EntityManager &entityManager) : m_entityManager(entityManager){};

  void init(int nbAsteroids, float boundaryV, float boundaryH);
  void fillPosEntityList(float *posEntities, int size, int *nbEntities, Utils::EntityType entityType);

private:
  entityx::EntityManager &m_entityManager;

  int m_nbAsteroids;
};
}// namespace AsteroidsCPP
