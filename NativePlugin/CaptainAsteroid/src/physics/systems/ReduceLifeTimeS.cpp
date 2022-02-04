#include "systems/ReduceLifeTimeS.hpp"

#include "components/LifeTimeC.hpp"
#include "components/IdentityC.hpp"
#include "components/DeathC.hpp"

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
      entity.assign<DeathC>();
    }
    else
    {
      live->lifeTime -= dt;
    }
  }
}
