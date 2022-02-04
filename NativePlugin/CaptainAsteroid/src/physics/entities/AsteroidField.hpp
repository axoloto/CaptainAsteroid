#pragma once

#include <array>

#include "Utils.hpp"

#include "entityx/System.h"

#include "components/AsteroidTypeC.hpp"

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

  void init(Utils::InitParams initParams);

  void fillPosEntityList(float *posEntities, int size, int *nbEntities, Utils::EntityType entityType);

  void createAsteroidsFromParent(entityx::Entity parent);

  void destroyAsteroid(entityx::Entity asteroid);

private:
  void initFieldWithRandomPos(Type type, float boundaryH, float boundaryV);

  entityx::EntityManager &m_entityManager;

  size_t m_nbMaxAsteroidsByType;

  size_t m_nbAsteroidsXXL;
  const float m_radiusXXL = 0.55f;

  size_t m_nbAsteroidsM;
  const float m_radiusM = 0.3f;

  size_t m_nbAsteroidsS;
  const float m_radiusS = 0.15f;
};
}// namespace AsteroidsCPP
