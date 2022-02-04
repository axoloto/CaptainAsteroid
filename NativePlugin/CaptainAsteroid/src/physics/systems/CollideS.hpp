#pragma once

#include "entities/AsteroidField.hpp"
#include "entities/LaserShots.hpp"

#include "components/PositionC.hpp"

#include "entityx/System.h"
#include "entityx/Event.h"

namespace AsteroidsCPP
{
class CollideS : public entityx::System<CollideS>
{
public:
  CollideS(AsteroidField &asteroidField, LaserShots &laserShots);

  void update(
    entityx::EntityManager &entities,
    entityx::EventManager &events,
    double dt);

private:
  void bounce(
    entityx::Entity entityA,
    entityx::Entity entityB);

  void destroyAsteroid(
    entityx::EntityManager &entities,
    entityx::Entity asteroid);

  void destroySpaceShip(
    entityx::EntityManager &entities,
    entityx::EventManager &events,
    entityx::Entity spaceShip);

  void destroyLaserShot(
    entityx::EntityManager &entities,
    entityx::Entity laserShot);

  void handleCollision(
    entityx::EntityManager &entities,
    entityx::EventManager &events,
    entityx::Entity entityA,
    entityx::Entity entityB);

  bool areColliding(
    const PositionC::Handle &pos1,
    float rad1,
    const PositionC::Handle &pos2,
    float rad2) const;

  AsteroidField &m_asteroidField;
  LaserShots &m_laserShots;
};
}// namespace AsteroidsCPP