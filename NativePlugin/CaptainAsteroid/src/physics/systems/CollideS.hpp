#pragma once

#include "components/PositionC.hpp"

#include "entityx/System.h"
#include "entityx/Event.h"

namespace CaptainAsteroidCPP
{
class CollideS : public entityx::System<CollideS>
{
public:
  CollideS() = default;

  void update(
    entityx::EntityManager &entities,
    entityx::EventManager &events,
    double dt);

private:
  bool areColliding(
    const PositionC::Handle &pos1,
    float rad1,
    const PositionC::Handle &pos2,
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
}// namespace CaptainAsteroidCPP