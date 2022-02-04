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
  LaserShots(entityx::EntityManager &entityManager) : m_entityManager(entityManager), m_shotVel(8.0f), m_maxNbShots(200), m_nbShots(0){};

  void fillPosEntityList(float *posEntities, int size, int *nbEntities, Utils::EntityType entityType) const;

  void createShot(const PositionC &initPos, const MotionC &initMot);
  void destroyShot(entityx::Entity shot);

private:
  entityx::EntityManager &m_entityManager;

  float m_shotVel;
  size_t m_maxNbShots;
  size_t m_nbShots;
};
}// namespace AsteroidsCPP
