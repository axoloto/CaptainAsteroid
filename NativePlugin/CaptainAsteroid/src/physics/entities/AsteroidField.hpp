#pragma once

#include <array>

#include "utils.hpp"

#include "entityx/System.h"

namespace AsteroidsCPP
{
class AsteroidField
{
public:
  AsteroidField(entityx::EntityManager &entityManager) : m_entityManager(entityManager),
                                                         m_nbMaxAsteroidsByType(200),
                                                         m_nbAsteroidsXXL(0),
                                                         m_nbAsteroidsM(0),
                                                         m_nbAsteroidsS(0){};

  void init(size_t nbAsteroids, float boundaryV, float boundaryH);
  void fillPosEntityList(float *posEntities, int size, int *nbEntities, Utils::EntityType entityType);

  void createAsteroidsFromParent(entityx::Entity parent);

  void destroyAsteroid(entityx::Entity asteroid);

private:
  entityx::EntityManager &m_entityManager;

  size_t m_nbMaxAsteroidsByType;
  size_t m_nbAsteroidsXXL;
  size_t m_nbAsteroidsM;
  size_t m_nbAsteroidsS;
};
}// namespace AsteroidsCPP
