#include "systems/ReduceLifeTime.hpp"

#include "components/LifeTime.hpp"
#include "components/Identity.hpp"
#include "components/Death.hpp"

using namespace CaptainAsteroidCPP::Sys;

void ReduceLifeTime::update(
  entityx::EntityManager &entities,
  entityx::EventManager &events,
  double dt)
{
  Comp::LifeTime::Handle live;
  Comp::Identity::Handle id;
  for (entityx::Entity entity : entities.entities_with_components(live, id))
  {
    if (live->lifeTime <= 0.0f)
    {
      entity.assign<Comp::Death>();
    }
    else
    {
      live->lifeTime -= dt;
    }
  }
}
