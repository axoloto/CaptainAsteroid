#include "systems/SplitAsteroid.hpp"

#include "components/Identity.hpp"
#include "components/AsteroidParent.hpp"

#include <cmath>

using namespace CaptainAsteroidCPP::Sys;

SplitAsteroid::SplitAsteroid(EntityHelper::AsteroidField &asteroidField)
  : m_asteroidField(asteroidField){};

void SplitAsteroid::update(
  entityx::EntityManager &entities,
  entityx::EventManager &events,
  double dt)
{
  Comp::Identity::Handle identity;
  Comp::AsteroidParent::Handle parent;
  for (entityx::Entity entity : entities.entities_with_components(identity, parent))
  {
    if (identity->id == Comp::Id::Asteroid)
    {
      m_asteroidField.createAsteroidsFromParent(entity);
    }
  }
}
