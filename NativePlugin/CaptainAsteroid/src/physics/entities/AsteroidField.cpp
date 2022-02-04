#include "AsteroidField.hpp"

#include "Utils.hpp"

#include "components/RadiusC.hpp"
#include "components/MotionC.hpp"
#include "components/PositionC.hpp"
#include "components/PlayerControlC.hpp"
#include "components/LifeTimeC.hpp"
#include "components/IdentityC.hpp"
#include "components/AsteroidTypeC.hpp"

#include <cmath>

using namespace AsteroidsCPP;

void AsteroidField::init(Utils::InitParams initParams)
{
  m_nbMaxAsteroidsByType = initParams.maxNbAsteroidsByType;

  m_nbAsteroidsXXL = initParams.initNbAsteroidsXXL;
  m_nbAsteroidsM = initParams.initNbAsteroidsM;
  m_nbAsteroidsS = initParams.initNbAsteroidsS;

  initFieldWithRandomPos(Type::XXL, initParams.boundaryDomainH, initParams.boundaryDomainV);
  initFieldWithRandomPos(Type::M, initParams.boundaryDomainH, initParams.boundaryDomainV);
  initFieldWithRandomPos(Type::S, initParams.boundaryDomainH, initParams.boundaryDomainV);
}

void AsteroidField::initFieldWithRandomPos(Type type, float boundaryH, float boundaryV)
{
  float radius = 0.0f;
  int nbAsteroids = 0;
  if (type == Type::XXL)
  {
    radius = m_radiusXXL;
    nbAsteroids = m_nbAsteroidsXXL;
  }
  else if (type == Type::M)
  {
    radius = m_radiusM;
    nbAsteroids = m_nbAsteroidsM;
  }
  else if (type == Type::S)
  {
    radius = m_radiusS;
    nbAsteroids = m_nbAsteroidsS;
  }

  for (size_t i = 0; i < nbAsteroids; ++i)
  {
    entityx::Entity asteroid = m_entityManager.create();
    asteroid.assign<IdentityC>(Id::Asteroid);
    asteroid.assign<AsteroidTypeC>(type);
    asteroid.assign<MotionC>((rand() % 100) / 30.0f + 0.5f, 0);

    float randX = (rand() % 100) / 50.0f * boundaryH - boundaryH;
    float randY = (rand() % 100) / 50.0f * boundaryV - boundaryV;

    //Quick hack to avoid asteroid generation around space ship
    if (abs(randX) < 1.0f) randX += 4.0f;
    if (abs(randY) < 1.0f) randY += 4.0f;

    asteroid.assign<PositionC>(randX, randY, rand() % 360);
    asteroid.assign<RadiusC>(radius);
  }
}

void AsteroidField::createAsteroidsFromParent(entityx::Entity parent)
{
  if (parent.has_component<AsteroidTypeC>() && parent.has_component<PositionC>())
  {
    auto type = parent.component<AsteroidTypeC>()->type;
    float xParent = parent.component<PositionC>()->x;
    float yParent = parent.component<PositionC>()->y;

    if (type == Type::XXL && m_nbAsteroidsM < m_nbMaxAsteroidsByType - 2)
    {
      entityx::Entity asteroid = m_entityManager.create();
      asteroid.assign<IdentityC>(Id::Asteroid);
      asteroid.assign<AsteroidTypeC>(Type::M);
      asteroid.assign<MotionC>((rand() % 100) / 30.0f + 0.5f, 0);
      asteroid.assign<PositionC>(xParent + m_radiusM, yParent + m_radiusM, (float)(rand() % 360));
      asteroid.assign<RadiusC>(m_radiusM);

      asteroid = m_entityManager.create();
      asteroid.assign<IdentityC>(Id::Asteroid);
      asteroid.assign<AsteroidTypeC>(Type::M);
      asteroid.assign<MotionC>((rand() % 100) / 30.0f + 0.5f, 0);
      asteroid.assign<PositionC>(xParent - m_radiusM, yParent - m_radiusM, (float)(rand() % 360));
      asteroid.assign<RadiusC>(m_radiusM);

      m_nbAsteroidsM += 2;
    }
    else if (type == Type::M && m_nbAsteroidsS < m_nbMaxAsteroidsByType - 2)
    {
      entityx::Entity asteroid = m_entityManager.create();
      asteroid.assign<IdentityC>(Id::Asteroid);
      asteroid.assign<AsteroidTypeC>(Type::S);
      asteroid.assign<MotionC>((rand() % 100) / 30.0f + 0.5f, 0);
      asteroid.assign<PositionC>(xParent + m_radiusS, yParent + m_radiusS, (float)(rand() % 360));
      asteroid.assign<RadiusC>(m_radiusS);

      asteroid = m_entityManager.create();
      asteroid.assign<IdentityC>(Id::Asteroid);
      asteroid.assign<AsteroidTypeC>(Type::S);
      asteroid.assign<MotionC>((rand() % 100) / 30.0f + 0.5f, 0);
      asteroid.assign<PositionC>(xParent - m_radiusS, yParent - m_radiusS, (float)(rand() % 360));
      asteroid.assign<RadiusC>(m_radiusS);

      m_nbAsteroidsS += 2;
    }
  }
}

void AsteroidField::destroyAsteroid(entityx::Entity asteroid)
{
  if (asteroid.has_component<AsteroidTypeC>())
  {
    auto type = asteroid.component<AsteroidTypeC>()->type;

    if (type == Type::XXL)
    {
      m_nbAsteroidsXXL--;
    }
    else if (type == Type::M)
    {
      m_nbAsteroidsM--;
    }
    else if (type == Type::S)
    {
      m_nbAsteroidsS--;
    }

    asteroid.destroy();
  }
}

void AsteroidField::fillPosEntityList(float *posEntities, int sizeBuffer, int *nbEntities, Utils::EntityType entityType) const
{
  int nbAsteroids = 0;
  auto selType = Type::Unknown;
  if (entityType == Utils::EntityType::Asteroid_XXL)
  {
    selType = Type::XXL;
    nbAsteroids = m_nbAsteroidsXXL;
  }
  else if (entityType == Utils::EntityType::Asteroid_M)
  {
    selType = Type::M;
    nbAsteroids = m_nbAsteroidsM;
  }
  else if (entityType == Utils::EntityType::Asteroid_S)
  {
    selType = Type::S;
    nbAsteroids = m_nbAsteroidsS;
  }

  PositionC::Handle position;
  IdentityC::Handle identity;
  AsteroidTypeC::Handle asteroidType;

  size_t i = 0;
  for (entityx::Entity entity : m_entityManager.entities_with_components(position, identity, asteroidType))
  {
    if (i >= sizeBuffer) break;// Should not happen
    if (identity->id != Id::Asteroid || asteroidType->type != selType) continue;

    posEntities[i++] = position->x;
    posEntities[i++] = position->y;
    posEntities[i++] = position->angle;
  }

  *nbEntities = (int)nbAsteroids;
}