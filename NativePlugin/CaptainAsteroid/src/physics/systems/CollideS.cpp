#include "systems/CollideS.hpp"

#include "components/PositionC.hpp"
#include "components/IdentityC.hpp"
#include "components/RadiusC.hpp"
#include "components/MotionC.hpp"
#include "components/AsteroidTypeC.hpp"
#include "components/AsteroidParentC.hpp"
#include "components/DeathC.hpp"

#include "events/GameOverE.hpp"

#include "Define.hpp"

#include <cmath>

using namespace AsteroidsCPP;

void CollideS::update(
  entityx::EntityManager &entities,
  entityx::EventManager &events,
  double dt)
{
  RadiusC::Handle sizeA;
  PositionC::Handle posA;
  IdentityC::Handle idA;
  for (entityx::Entity entityA : entities.entities_with_components(sizeA, posA, idA))
  {
    // This entity has been destroyed in a previous collision, it will be removed soon
    if (entityA.has_component<DeathC>())
    {
      continue;
    }

    RadiusC::Handle sizeB;
    PositionC::Handle posB;
    IdentityC::Handle idB;
    for (entityx::Entity entityB : entities.entities_with_components(sizeB, posB, idB))
    {
      if ((entityB == entityA)
          || !entityA.valid()
          || !entityB.valid()
          || entityB.has_component<DeathC>()
          || entityA.has_component<DeathC>()
          // Not interested by
          // space ship/laser shot
          // laser shot/laser shot
          // interactions for now
          || (idA->id == Id::LaserShot && idB->id == Id::SpaceShip)
          || (idB->id == Id::LaserShot && idA->id == Id::SpaceShip)
          || (idB->id == Id::LaserShot && idA->id == Id::LaserShot))
      {
        continue;
      }

      if (areColliding(posA, sizeA->radius, posB, sizeB->radius))
      {
        handleCollision(entities, events, entityA, entityB);
      }
    }
  }
}

void CollideS::handleCollision(
  entityx::EntityManager &entities,
  entityx::EventManager &events,
  entityx::Entity entityA,
  entityx::Entity entityB)
{
  IdentityC::Handle idA = entityA.component<IdentityC>();
  IdentityC::Handle idB = entityB.component<IdentityC>();

  if (idA->id == Id::Asteroid && idB->id == Id::Asteroid)
  {
    // Asteroids are bouncing again each other (in an approximate way)
    bounceAsteroids(entityA, entityB);
  }
  else if (idA->id == Id::Asteroid && idB->id == Id::LaserShot)
  {
    splitAsteroid(entityA);
    // Laser shot also removed
    entityB.assign<DeathC>();
  }
  else if (idA->id == Id::LaserShot && idB->id == Id::Asteroid)
  {
    // Recursive call with swapped entities
    handleCollision(entities, events, entityB, entityA);
  }
  else if (idA->id == Id::SpaceShip && idB->id == Id::Asteroid)
  {
    // Captain Asteroid going down!
    entityA.assign<DeathC>();
  }
  else if (idA->id == Id::Asteroid && idB->id == Id::SpaceShip)
  {
    // Recursive call with swapped entities
    handleCollision(entities, events, entityB, entityA);
  }
}

void CollideS::bounceAsteroids(
  entityx::Entity asteroidA,
  entityx::Entity asteroidB)
{
  PositionC::Handle posA = asteroidA.component<PositionC>();
  PositionC::Handle posB = asteroidB.component<PositionC>();

  float angle = 90.0f;
  if ((posB->y - posA->y) >= 0.01f)
  {
    angle = atan((posB->x - posA->x) / (posB->y - posA->y)) * 180.0f / Def::PI;
  }

  if (posB->x > posA->x)
  {
    float sign = (posB->y > posA->y) ? 1.0f : -1.0f;
    posB->angle = sign * angle;
    posA->angle = sign * angle + 180.0f;
  }
  else
  {
    float sign = (posB->y > posA->y) ? -1.0f : 1.0f;
    posB->angle = sign * angle + 180.0f;
    posA->angle = sign * angle;
  }
}

void CollideS::splitAsteroid(entityx::Entity asteroid)
{
  AsteroidTypeC::Handle asteroidType = asteroid.component<AsteroidTypeC>();
  if (asteroidType && (asteroidType->type == Type::XXL || asteroidType->type == Type::M))
  {
    // For M and XXL asteroids, we will create children later on in the pipeline
    asteroid.assign<AsteroidParentC>();
  }
  // Both laser shot and parent asteroid will be removed
  asteroid.assign<DeathC>();
}

bool CollideS::areColliding(
  const PositionC::Handle &pos1,
  float rad1,
  const PositionC::Handle &pos2,
  float rad2) const
{
  return (pos1->dist2(*pos2) < (rad1 + rad2) * (rad1 + rad2));
}
