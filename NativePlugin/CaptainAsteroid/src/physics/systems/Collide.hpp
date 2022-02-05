#pragma once

#include "components/Position.hpp"

#include "entityx/System.h"
#include "entityx/Event.h"

namespace CaptainAsteroidCPP
{
namespace Sys
{
  class Collide : public entityx::System<Collide>
  {
  public:
    Collide() = default;

    void update(
      entityx::EntityManager &entities,
      entityx::EventManager &events,
      double dt);

  private:
    bool areColliding(
      const Comp::Position::Handle &pos1,
      float rad1,
      const Comp::Position::Handle &pos2,
      float rad2) const;

    void handleCollision(
      entityx::EntityManager &entities,
      entityx::EventManager &events,
      entityx::Entity entityA,
      entityx::Entity entityB);

    void bounceAsteroids(
      entityx::Entity asteroidA,
      entityx::Entity asteroidB);

    void splitAsteroid(
      entityx::Entity asteroid);
  };
}// namespace Sys
}// namespace CaptainAsteroidCPP