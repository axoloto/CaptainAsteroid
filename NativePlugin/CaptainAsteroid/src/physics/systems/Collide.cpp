#include "systems/Collide.hpp"

#include "components/Position.hpp"
#include "components/Identity.hpp"
#include "components/Radius.hpp"
#include "components/Motion.hpp"
#include "components/AsteroidSize.hpp"
#include "components/AsteroidParent.hpp"
#include "components/Death.hpp"

#include "events/GameOver.hpp"

#include "Define.hpp"

#include <cmath>

using namespace CaptainAsteroidCPP::Sys;

void Collide::update(
  entityx::EntityManager &entities,
  entityx::EventManager &events,
  double dt)
{
  Comp::Radius::Handle sizeA;
  Comp::Position::Handle posA;
  Comp::Identity::Handle idA;
  for (entityx::Entity entityA : entities.entities_with_components(sizeA, posA, idA))
  {
    // This entity has been destroyed in a previous collision, it will be removed soon
    if (entityA.has_component<Comp::Death>())
    {
      continue;
    }

    Comp::Radius::Handle sizeB;
    Comp::Position::Handle posB;
    Comp::Identity::Handle idB;
    for (entityx::Entity entityB : entities.entities_with_components(sizeB, posB, idB))
    {
      if ((entityB == entityA)
          || !entityA.valid()
          || !entityB.valid()
          || entityB.has_component<Comp::Death>()
          || entityA.has_component<Comp::Death>()
          // Not interested by
          // space ship/laser shot
          // laser shot/laser shot
          // interactions for now
          || (idA->id == Comp::Id::LaserShot && idB->id == Comp::Id::SpaceShip)
          || (idB->id == Comp::Id::LaserShot && idA->id == Comp::Id::SpaceShip)
          || (idB->id == Comp::Id::LaserShot && idA->id == Comp::Id::LaserShot))
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

void Collide::handleCollision(
  entityx::EntityManager &entities,
  entityx::EventManager &events,
  entityx::Entity entityA,
  entityx::Entity entityB)
{
  Comp::Identity::Handle idA = entityA.component<Comp::Identity>();
  Comp::Identity::Handle idB = entityB.component<Comp::Identity>();

  if (idA->id == Comp::Id::Asteroid && idB->id == Comp::Id::Asteroid)
  {
    // Asteroids are bouncing again each other (in an approximate way)
    bounceAsteroids(entityA, entityB);
  }
  else if (idA->id == Comp::Id::Asteroid && idB->id == Comp::Id::LaserShot)
  {
    splitAsteroid(entityA);
    // Laser shot also removed
    entityB.assign<Comp::Death>();
  }
  else if (idA->id == Comp::Id::LaserShot && idB->id == Comp::Id::Asteroid)
  {
    // Recursive call with swapped entities
    handleCollision(entities, events, entityB, entityA);
  }
  else if (idA->id == Comp::Id::SpaceShip && idB->id == Comp::Id::Asteroid)
  {
    // Captain Asteroid going down!
    entityA.assign<Comp::Death>();
  }
  else if (idA->id == Comp::Id::Asteroid && idB->id == Comp::Id::SpaceShip)
  {
    // Recursive call with swapped entities
    handleCollision(entities, events, entityB, entityA);
  }
}

void Collide::bounceAsteroids(
  entityx::Entity asteroidA,
  entityx::Entity asteroidB)
{
  Comp::Position::Handle posA = asteroidA.component<Comp::Position>();
  Comp::Position::Handle posB = asteroidB.component<Comp::Position>();

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

void Collide::splitAsteroid(entityx::Entity asteroid)
{
  Comp::AsteroidSize::Handle asteroidSize = asteroid.component<Comp::AsteroidSize>();
  if (asteroidSize && (asteroidSize->size == Comp::AstSize::XXL || asteroidSize->size == Comp::AstSize::M))
  {
    // For M and XXL asteroids, we will create children later on in the pipeline
    asteroid.assign<Comp::AsteroidParent>();
  }
  // Both laser shot and parent asteroid will be removed
  asteroid.assign<Comp::Death>();
}

bool Collide::areColliding(
  const Comp::Position::Handle &pos1,
  float rad1,
  const Comp::Position::Handle &pos2,
  float rad2) const
{
  return (pos1->dist2(*pos2) < (rad1 + rad2) * (rad1 + rad2));
}
