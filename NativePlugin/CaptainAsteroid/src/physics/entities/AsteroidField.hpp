#pragma once

#include <array>

#include "Define.hpp"

#include "entityx/System.h"

#include "components/AsteroidSize.hpp"

namespace CaptainAsteroidCPP
{
namespace EntityHelper
{
  class AsteroidField
  {
  public:
    AsteroidField(entityx::EntityManager &entityManager,
      entityx::EventManager &eventManager) : m_entityManager(entityManager),
                                             m_eventManager(eventManager),
                                             m_nbMaxAsteroidsBySize(200),
                                             m_nbAsteroidsXXL(0),
                                             m_nbAsteroidsM(0),
                                             m_nbAsteroidsS(0){};

    void init(Def::InitParams initParams);

    void fillPosEntityList(float *posEntities, int size, int *nbEntities, Def::EntityType entityType) const;

    void createAsteroidsFromParent(entityx::Entity parent);

    void destroyAsteroid(entityx::Entity asteroid);

    int totalNbAsteroids() const { return m_nbAsteroidsXXL + m_nbAsteroidsM + m_nbAsteroidsS; }

  private:
    void initFieldWithRandomPos(Comp::AstSize type, float boundaryH, float boundaryV);

    entityx::EntityManager &m_entityManager;
    entityx::EventManager &m_eventManager;

    size_t m_nbMaxAsteroidsBySize;

    size_t m_nbAsteroidsXXL;
    const float m_radiusXXL = 0.55f;

    size_t m_nbAsteroidsM;
    const float m_radiusM = 0.3f;

    size_t m_nbAsteroidsS;
    const float m_radiusS = 0.15f;
  };
}// namespace EntityHelper
}// namespace CaptainAsteroidCPP
