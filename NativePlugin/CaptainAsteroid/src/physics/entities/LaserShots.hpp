#pragma once

#include "Utils.hpp"

#include "entityx/System.h"

#include "components/MotionC.hpp"
#include "components/PositionC.hpp"

#include <array>

namespace AsteroidsCPP
{
class LaserShots
{
public:
  LaserShots(entityx::EntityManager &entityManager) : m_entityManager(entityManager), m_nbShots(0), m_maxNbShots(200){};

  void fillPosEntityList(float *posEntities, int size, int *nbEntities, Utils::EntityType entityType);

  void createShot(const PositionC &initPos);
  void destroyShot(entityx::Entity shot);

private:
  entityx::EntityManager &m_entityManager;

  const float m_shotVel = 8.0f;
  size_t m_nbShots;
  size_t m_maxNbShots;
};
}// namespace AsteroidsCPP
