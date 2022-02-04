#include "systems/ReduceLifeTimeS.hpp"

#include "components/LifeTimeC.hpp"
#include "components/IdentityC.hpp"

using namespace AsteroidsCPP;

void ReduceLifeTimeS::update(
  entityx::EntityManager &entities,
  entityx::EventManager &events,
  double dt)
{
  LifeTimeC::Handle live;
  IdentityC::Handle id;
  for (entityx::Entity entity : entities.entities_with_components(live, id))
  {
    if (live->lifeTime <= 0.0f)
    {
      if (entity.component<IdentityC>()->id == Id::LaserShot)
        m_laserShots.destroyShot(entity);
      else
        entity.destroy();
    }
    else
    {
      live->lifeTime -= dt;
    }
  }
}
