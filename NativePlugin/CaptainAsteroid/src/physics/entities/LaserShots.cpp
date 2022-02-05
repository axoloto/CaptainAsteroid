#include "entities/LaserShots.hpp"

#include "Define.hpp"

#include "components/RadiusC.hpp"
#include "components/LifeTimeC.hpp"
#include "components/IdentityC.hpp"

using namespace AsteroidsCPP;

void LaserShots::createShot(const PositionC &initPos, const MotionC &initMot)
{
  if (m_nbShots < m_maxNbShots)
  {
    entityx::Entity laserShot = m_entityManager.create();
    laserShot.assign<IdentityC>(Id::LaserShot);
    laserShot.assign<MotionC>(m_shotVel + initMot.vel, 0.0f);
    laserShot.assign<PositionC>(initPos);
    laserShot.assign<LifeTimeC>(1.5f);
    laserShot.assign<RadiusC>(0.1f);
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
  PositionC::Handle position;
  LifeTimeC::Handle lifeTime;
  IdentityC::Handle identity;

  int i = 0;
  for (entityx::Entity entity : m_entityManager.entities_with_components(identity, position, lifeTime))
  {
    if (identity->id != Id::LaserShot) continue;

    if (i < sizeBuffer)
    {
      posEntities[i++] = position->x;
      posEntities[i++] = position->y;
      posEntities[i++] = position->angle;
    }
  }

  *nbEntities = (int)m_nbShots;
}
