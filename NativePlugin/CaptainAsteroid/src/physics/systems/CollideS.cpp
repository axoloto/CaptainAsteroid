#include "systems/CollideS.hpp"

#include "components/PositionC.hpp"
#include "components/PlayerControlC.hpp"
#include "components/LifeTimeC.hpp"
#include "components/IdentityC.hpp"
#include "components/RadiusC.hpp"
#include "components/MotionC.hpp"
#include "components/AsteroidTypeC.hpp"
#include "components/AsteroidParentC.hpp"
#include "components/DeathC.hpp"

#include "events/GameOverE.hpp"

#include <cmath>

using namespace AsteroidsCPP;

CollideS::CollideS(AsteroidField &asteroidField, LaserShots &laserShots)
  : m_asteroidField(asteroidField),
    m_laserShots(laserShots){};

void CollideS::update(
  entityx::EntityManager &entities,
  entityx::EventManager &events,
  double dt)
{
  RadiusC::Handle sizeA;
  PositionC::Handle posA;
  IdentityC::Handle idA;
  MotionC::Handle motionA;
  for (entityx::Entity entityA : entities.entities_with_components(sizeA, posA, idA, motionA))
  {
    if (entityA.has_component<DeathC>())
    {
      continue;
    }

    RadiusC::Handle sizeB;
    PositionC::Handle posB;
    IdentityC::Handle idB;
    MotionC::Handle motionB;
    for (entityx::Entity entityB : entities.entities_with_components(sizeB, posB, idB, motionB))
    {
      if ((entityB == entityA)
          || !entityA.valid()
          || !entityB.valid()
          || entityB.has_component<DeathC>()
          || entityA.has_component<DeathC>()
          // Not interested by space ship/laser shot
          // and laser shot/laser shot interactions for now
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
    bounce(entityA, entityB);
  }
  else if (idA->id == Id::Asteroid && idB->id == Id::LaserShot)
  {
    //destroyAsteroid(entities, entityA);

    AsteroidTypeC::Handle asteroidType = entityA.component<AsteroidTypeC>();
    if (asteroidType)
    {
      if (asteroidType->type == Type::XXL || asteroidType->type == Type::M)
      {
        entityA.assign<AsteroidParentC>();
        //m_asteroidField.createAsteroidsFromParent(entityA);
      }
    }

    entityA.assign<DeathC>();
    entityB.assign<DeathC>();
  }
  else if (idA->id == Id::LaserShot && idB->id == Id::Asteroid)
  {
    // Recursive call with swapped entities
    handleCollision(entities, events, entityB, entityA);
  }
  else if (idA->id == Id::SpaceShip && idB->id == Id::Asteroid)
  {
    float x = entityA.component<PositionC>()->x;
    float y = entityA.component<PositionC>()->y;
    entityA.assign<DeathC>();

    // destroySpaceShip(entities, events, entityA);
  }
  else if (idA->id == Id::Asteroid && idB->id == Id::SpaceShip)
  {
    // Recursive call with swapped entities
    handleCollision(entities, events, entityB, entityA);
  }
}

void CollideS::bounce(
  entityx::Entity entityA,
  entityx::Entity entityB)
{
  PositionC::Handle posA = entityA.component<PositionC>();
  PositionC::Handle posB = entityB.component<PositionC>();

  float angle = 90.0f;
  if ((posB->y - posA->y) >= 0.01f)
  {
    angle = atan((posB->x - posA->x) / (posB->y - posA->y)) * 180.0f / Utils::PI;
  }

  if (posB->x > posA->x)
  {
    if (posB->y > posA->y)
    {
      posB->angle = angle;
      posA->angle = angle + 180.0f;
    }
    else
    {
      posB->angle = -angle;
      posA->angle = -angle + 180.0f;
    }
  }
  else
  {
    if (posB->y > posA->y)
    {
      posB->angle = -angle + 180.0f;
      posA->angle = -angle;
    }
    else
    {
      posB->angle = angle + 180.0f;
      posA->angle = angle;
    }
  }
}
/*
void CollideS::destroyAsteroid(
  entityx::EntityManager &entities,
  entityx::Entity asteroid)
{
  AsteroidTypeC::Handle asteroidType = asteroid.component<AsteroidTypeC>();
  if (asteroidType)
  {
    if (asteroidType->type == Type::XXL || asteroidType->type == Type::M)
    {
      m_asteroidField.createAsteroidsFromParent(asteroid);
    }
    // m_asteroidField.destroyAsteroid(asteroid);
  }
}

void CollideS::destroyLaserShot(
  entityx::EntityManager &entities,
  entityx::Entity laserShot)
{
  IdentityC::Handle idLs = laserShot.component<IdentityC>();
  if (idLs->id == Id::LaserShot)
  {
    // m_laserShots.destroyShot(laserShot);
  }
}

void CollideS::destroySpaceShip(
  entityx::EntityManager &entities,
  entityx::EventManager &events,
  entityx::Entity spaceShip)
{
  //events.emit<GameOverE>();
}
*/
bool CollideS::areColliding(
  const PositionC::Handle &pos1,
  float rad1,
  const PositionC::Handle &pos2,
  float rad2) const
{
  return (pos1->dist2(*pos2) < (rad1 + rad2) * (rad1 + rad2));
}
