
#include "systems/FireLaserS.hpp"

#include "components/MotionC.hpp"
#include "components/PositionC.hpp"
#include "components/LaserC.hpp"
#include "components/LifeTimeC.hpp"

using namespace AsteroidsCPP;

void FireLaserS::update(entityx::EntityManager &entities,
  entityx::EventManager &events,
  double dt)
{
  MotionC::Handle motion;
  PositionC::Handle position;
  LaserC::Handle laser;
  for (entityx::Entity entity : entities.entities_with_components(motion, position, laser))
  {
    laser->nextShotTimer -= dt;

    if (laser->isFiring && laser->nextShotTimer <= 0.0f)
    {
      m_laserShots.createShot(*position.get());
      laser->nextShotTimer = laser->coolDownTime;
    }
  }
}
