#include "systems/RemoveDead.hpp"

#include "components/Identity.hpp"
#include "components/Death.hpp"

#include "events/GameOver.hpp"

#include <cmath>

using namespace CaptainAsteroidCPP::Sys;

RemoveDead::RemoveDead(
  EntityHelper::AsteroidField &asteroidField,
  EntityHelper::LaserShots &laserShots)
  : m_asteroidField(asteroidField),
    m_laserShots(laserShots){};

void RemoveDead::update(
  entityx::EntityManager &entities,
  entityx::EventManager &events,
  double dt)
{
  Comp::Death::Handle death;
  Comp::Identity::Handle identity;
  for (entityx::Entity entity : entities.entities_with_components(death, identity))
  {
    if (identity->id == Comp::Id::Asteroid)
    {
      m_asteroidField.destroyAsteroid(entity);
    }
    else if (identity->id == Comp::Id::LaserShot)
    {
      m_laserShots.destroyShot(entity);
    }
    else if (identity->id == Comp::Id::SpaceShip)
    {
      entity.destroy();
      events.emit<Ev::GameOver>();
    }
  }
}
