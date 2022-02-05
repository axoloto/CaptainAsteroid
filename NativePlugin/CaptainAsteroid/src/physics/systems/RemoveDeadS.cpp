#include "systems/RemoveDeadS.hpp"

#include "components/IdentityC.hpp"
#include "components/DeathC.hpp"

#include "events/GameOverE.hpp"

#include <cmath>

using namespace CaptainAsteroidCPP;

RemoveDeadS::RemoveDeadS(AsteroidField &asteroidField, LaserShots &laserShots)
  : m_asteroidField(asteroidField),
    m_laserShots(laserShots){};

void RemoveDeadS::update(
  entityx::EntityManager &entities,
  entityx::EventManager &events,
  double dt)
{
  DeathC::Handle death;
  IdentityC::Handle identity;
  for (entityx::Entity entity : entities.entities_with_components(death, identity))
  {
    if (identity->id == Id::Asteroid)
    {
      m_asteroidField.destroyAsteroid(entity);
    }
    else if (identity->id == Id::LaserShot)
    {
      m_laserShots.destroyShot(entity);
    }
    else if (identity->id == Id::SpaceShip)
    {
      entity.destroy();
      events.emit<GameOverE>();
    }
  }
}
