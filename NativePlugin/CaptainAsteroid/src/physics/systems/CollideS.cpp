#include "systems/CollideS.hpp"

#include "components/PositionC.hpp"
#include "components/PlayerControlC.hpp"
#include "components/LifeTimeC.hpp"
#include "components/IdentityC.hpp"
#include "components/RadiusC.hpp"
#include "components/MotionC.hpp"

#include "events/GameOverE.hpp"

#include <cmath>

using namespace AsteroidsCPP;

CollideS::CollideS(AsteroidField &asteroidField) : m_asteroidField(asteroidField){};

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
    RadiusC::Handle sizeB;
    PositionC::Handle posB;
    IdentityC::Handle idB;
    MotionC::Handle motionB;
    for (entityx::Entity entityB : entities.entities_with_components(sizeB, posB, idB, motionB))
    {
      if (entityB == entityA)
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
  else if ((idA->id == Id::LaserShot && idB->id == Id::Asteroid)
           || (idA->id == Id::Asteroid && idB->id == Id::LaserShot))
  {
    destroyAsteroid(entities, idA->id == Id::Asteroid ? entityA : entityB);
  }
  else if ((idA->id == Id::SpaceShip && idB->id == Id::Asteroid)
           || (idA->id == Id::Asteroid && idB->id == Id::SpaceShip))
  {
    destroySpaceShip(entities, events, idA->id == Id::SpaceShip ? entityA : entityB);
  }
}

void CollideS::bounce(
  entityx::Entity entityA,
  entityx::Entity entityB)
{
  MotionC::Handle motionA = entityA.component<MotionC>();
  PositionC::Handle posA = entityA.component<PositionC>();

  MotionC::Handle motionB = entityB.component<MotionC>();
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

void CollideS::destroyAsteroid(
  entityx::EntityManager &entities,
  entityx::Entity asteroid)
{
  m_asteroidField.removeAsteroid(asteroid);
}

void CollideS::destroySpaceShip(
  entityx::EntityManager &entities,
  entityx::EventManager &events,
  entityx::Entity spaceShip)
{
  events.emit<GameOverE>();
}

bool CollideS::areColliding(
  const PositionC::Handle &pos1,
  float rad1,
  const PositionC::Handle &pos2,
  float rad2) const
{
  return (pos1->dist2(*pos2) < (rad1 + rad2) * (rad1 + rad2));
}
