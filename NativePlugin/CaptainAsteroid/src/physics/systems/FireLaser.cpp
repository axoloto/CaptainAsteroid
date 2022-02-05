
#include "systems/FireLaser.hpp"

#include "components/Motion.hpp"
#include "components/Position.hpp"
#include "components/Laser.hpp"
#include "components/LifeTime.hpp"

using namespace CaptainAsteroidCPP::Sys;

void FireLaser::update(entityx::EntityManager &entities,
  entityx::EventManager &events,
  double dt)
{
  Comp::Laser::Handle laser;
  Comp::Motion::Handle motion;
  Comp::Position::Handle position;
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
