#pragma once

#include "Define.hpp"

#include "entityx/System.h"

#include "components/Motion.hpp"
#include "components/Position.hpp"

#include <array>

namespace CaptainAsteroidCPP
{
namespace EntityHelper
{
  class LaserShots
  {
  public:
    LaserShots(entityx::EntityManager &entityManager) : m_entityManager(entityManager), m_shotVel(8.0f), m_maxNbShots(200), m_nbShots(0){};

    void fillPosEntityList(float *posEntities, int size, int *nbEntities, Def::EntityType entityType) const;

    void createShot(const Comp::Position &initPos, const Comp::Motion &initMot);
    void destroyShot(entityx::Entity shot);

  private:
    entityx::EntityManager &m_entityManager;

    float m_shotVel;
    size_t m_maxNbShots;
    size_t m_nbShots;
  };
}// namespace EntityHelper
}// namespace CaptainAsteroidCPP
