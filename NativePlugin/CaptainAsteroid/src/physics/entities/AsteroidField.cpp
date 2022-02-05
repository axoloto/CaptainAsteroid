#include "AsteroidField.hpp"

#include "Define.hpp"

#include "components/RadiusC.hpp"
#include "components/MotionC.hpp"
#include "components/PositionC.hpp"
#include "components/PlayerControlC.hpp"
#include "components/LifeTimeC.hpp"
#include "components/IdentityC.hpp"
#include "components/AsteroidSizeC.hpp"

#include "events/AsteroidDestroyedE.hpp"
#include "events/VictoryE.hpp"

#include <cmath>

using namespace AsteroidsCPP;

void AsteroidField::init(Def::InitParams initParams)
{
  m_nbMaxAsteroidsByType = initParams.maxNbAsteroidsByType;

  m_nbAsteroidsXXL = initParams.initNbAsteroidsXXL;
  m_nbAsteroidsM = initParams.initNbAsteroidsM;
  m_nbAsteroidsS = initParams.initNbAsteroidsS;

  initFieldWithRandomPos(AstSize::XXL, initParams.boundaryDomainH, initParams.boundaryDomainV);
  initFieldWithRandomPos(AstSize::M, initParams.boundaryDomainH, initParams.boundaryDomainV);
  initFieldWithRandomPos(AstSize::S, initParams.boundaryDomainH, initParams.boundaryDomainV);

  // Empty field, nothing to do
  if (totalNbAsteroids() == 0)
  {
    m_eventManager.emit<VictoryE>();
  }
}

void AsteroidField::initFieldWithRandomPos(AstSize type, float boundaryH, float boundaryV)
{
  float radius = 0.0f;
  int nbAsteroids = 0;
  if (type == AstSize::XXL)
  {
    radius = m_radiusXXL;
    nbAsteroids = m_nbAsteroidsXXL;
  }
  else if (type == AstSize::M)
  {
    radius = m_radiusM;
    nbAsteroids = m_nbAsteroidsM;
  }
  else if (type == AstSize::S)
  {
    radius = m_radiusS;
    nbAsteroids = m_nbAsteroidsS;
  }

  for (size_t i = 0; i < nbAsteroids; ++i)
  {
    entityx::Entity asteroid = m_entityManager.create();
    asteroid.assign<IdentityC>(Id::Asteroid);
    asteroid.assign<AsteroidSizeC>(type);
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
  if (parent.has_component<AsteroidSizeC>() && parent.has_component<PositionC>())
  {
    auto type = parent.component<AsteroidSizeC>()->type;
    float xParent = parent.component<PositionC>()->x;
    float yParent = parent.component<PositionC>()->y;

    if (type == AstSize::XXL && m_nbAsteroidsM < m_nbMaxAsteroidsByType - 2)
    {
      entityx::Entity asteroid = m_entityManager.create();
      asteroid.assign<IdentityC>(Id::Asteroid);
      asteroid.assign<AsteroidSizeC>(AstSize::M);
      asteroid.assign<MotionC>((rand() % 100) / 30.0f + 0.5f, 0);
      asteroid.assign<PositionC>(xParent + m_radiusM, yParent + m_radiusM, (float)(rand() % 360));
      asteroid.assign<RadiusC>(m_radiusM);

      asteroid = m_entityManager.create();
      asteroid.assign<IdentityC>(Id::Asteroid);
      asteroid.assign<AsteroidSizeC>(AstSize::M);
      asteroid.assign<MotionC>((rand() % 100) / 30.0f + 0.5f, 0);
      asteroid.assign<PositionC>(xParent - m_radiusM, yParent - m_radiusM, (float)(rand() % 360));
      asteroid.assign<RadiusC>(m_radiusM);

      m_nbAsteroidsM += 2;
    }
    else if (type == AstSize::M && m_nbAsteroidsS < m_nbMaxAsteroidsByType - 2)
    {
      entityx::Entity asteroid = m_entityManager.create();
      asteroid.assign<IdentityC>(Id::Asteroid);
      asteroid.assign<AsteroidSizeC>(AstSize::S);
      asteroid.assign<MotionC>((rand() % 100) / 30.0f + 0.5f, 0);
      asteroid.assign<PositionC>(xParent + m_radiusS, yParent + m_radiusS, (float)(rand() % 360));
      asteroid.assign<RadiusC>(m_radiusS);

      asteroid = m_entityManager.create();
      asteroid.assign<IdentityC>(Id::Asteroid);
      asteroid.assign<AsteroidSizeC>(AstSize::S);
      asteroid.assign<MotionC>((rand() % 100) / 30.0f + 0.5f, 0);
      asteroid.assign<PositionC>(xParent - m_radiusS, yParent - m_radiusS, (float)(rand() % 360));
      asteroid.assign<RadiusC>(m_radiusS);

      m_nbAsteroidsS += 2;
    }
  }
}

void AsteroidField::destroyAsteroid(entityx::Entity asteroid)
{
  if (asteroid.has_component<AsteroidSizeC>())
  {
    auto type = asteroid.component<AsteroidSizeC>()->type;

    if (type == AstSize::XXL)
    {
      m_nbAsteroidsXXL--;
    }
    else if (type == AstSize::M)
    {
      m_nbAsteroidsM--;
    }
    else if (type == AstSize::S)
    {
      m_nbAsteroidsS--;
    }

    m_eventManager.emit<AsteroidDestroyedE>(type);

    if (totalNbAsteroids() == 0)
    {
      m_eventManager.emit<VictoryE>();
    }

    asteroid.destroy();
  }
}

void AsteroidField::fillPosEntityList(float *posEntities, int sizeBuffer, int *nbEntities, Def::EntityType entityType) const
{
  int nbAsteroids = 0;
  auto selSize = AstSize::Unknown;
  if (entityType == Def::EntityType::Asteroid_XXL)
  {
    selSize = AstSize::XXL;
    nbAsteroids = m_nbAsteroidsXXL;
  }
  else if (entityType == Def::EntityType::Asteroid_M)
  {
    selSize = AstSize::M;
    nbAsteroids = m_nbAsteroidsM;
  }
  else if (entityType == Def::EntityType::Asteroid_S)
  {
    selSize = AstSize::S;
    nbAsteroids = m_nbAsteroidsS;
  }

  PositionC::Handle position;
  IdentityC::Handle identity;
  AsteroidSizeC::Handle asteroidSize;

  size_t i = 0;
  for (entityx::Entity entity : m_entityManager.entities_with_components(position, identity, asteroidSize))
  {
    if (identity->id != Id::Asteroid || asteroidSize->type != selSize) continue;

    if (i < sizeBuffer)
    {
      posEntities[i++] = position->x;
      posEntities[i++] = position->y;
      posEntities[i++] = position->angle;
    }
  }

  *nbEntities = (int)nbAsteroids;
}