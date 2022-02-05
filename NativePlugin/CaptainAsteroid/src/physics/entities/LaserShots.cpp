#include "entities/LaserShots.hpp"

#include "Define.hpp"

#include "components/Radius.hpp"
#include "components/LifeTime.hpp"
#include "components/Identity.hpp"

using namespace CaptainAsteroidCPP::EntityHelper;

void LaserShots::createShot(const Comp::Position &initPos, const Comp::Motion &initMot)
{
  if (m_nbShots < m_maxNbShots)
  {
    entityx::Entity laserShot = m_entityManager.create();
    laserShot.assign<Comp::Identity>(Comp::Id::LaserShot);
    laserShot.assign<Comp::Motion>(m_shotVel + initMot.vel, 0.0f);
    laserShot.assign<Comp::Position>(initPos);
    laserShot.assign<Comp::LifeTime>(1.5f);
    laserShot.assign<Comp::Radius>(0.1f);
    m_nbShots++;
  }
}

void LaserShots::destroyShot(entityx::Entity shot)
{
  shot.destroy();
  m_nbShots--;
}

void LaserShots::fillPosEntityList(float *posEntities, int sizeBuffer, int *nbEntities, Def::EntityType entityType) const
{
  Comp::Position::Handle position;
  Comp::LifeTime::Handle lifeTime;
  Comp::Identity::Handle identity;

  int i = 0;
  for (entityx::Entity entity : m_entityManager.entities_with_components(identity, position, lifeTime))
  {
    if (identity->id != Comp::Id::LaserShot) continue;

    if (i < sizeBuffer)
    {
      posEntities[i++] = position->x;
      posEntities[i++] = position->y;
      posEntities[i++] = position->angle;
    }
  }

  *nbEntities = (int)m_nbShots;
}
