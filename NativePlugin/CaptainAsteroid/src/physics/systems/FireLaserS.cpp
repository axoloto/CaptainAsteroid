
#include "systems/FireLaserS.hpp"

#include "components/MotionC.hpp"
#include "components/PositionC.hpp"
#include "components/LaserC.hpp"
#include "components/LifeTimeC.hpp"

using namespace CaptainAsteroidCPP;

void FireLaserS::update(entityx::EntityManager &entities,
  entityx::EventManager &events,
  double dt)
{
  LaserC::Handle laser;
  MotionC::Handle motion;
  PositionC::Handle position;
  for (entityx::Entity entity : entities.entities_with_components(laser, motion, position))
  {
    laser->nextShotTimer -= dt;

    if (laser->isFiring && laser->nextShotTimer <= 0.0f)
    {
      m_laserShots.createShot(*position.get(), *motion.get());
      laser->nextShotTimer = laser->coolDownTime;
    }
  }
}
