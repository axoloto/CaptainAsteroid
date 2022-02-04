#include "systems/SplitAsteroidS.hpp"

#include "components/IdentityC.hpp"
#include "components/AsteroidParentC.hpp"

#include <cmath>

using namespace AsteroidsCPP;

SplitAsteroidS::SplitAsteroidS(AsteroidField &asteroidField)
  : m_asteroidField(asteroidField){};

void SplitAsteroidS::update(
  entityx::EntityManager &entities,
  entityx::EventManager &events,
  double dt)
{
  IdentityC::Handle identity;
  AsteroidParentC::Handle parent;
  for (entityx::Entity entity : entities.entities_with_components(identity, parent))
  {
    if (identity->id == Id::Asteroid)
    {
      m_asteroidField.createAsteroidsFromParent(entity);
    }
  }
}
