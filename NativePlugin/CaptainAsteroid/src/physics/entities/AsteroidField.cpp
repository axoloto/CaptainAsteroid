#include "AsteroidField.hpp"

#include "Define.hpp"

#include "components/Radius.hpp"
#include "components/Motion.hpp"
#include "components/Position.hpp"
#include "components/PlayerControl.hpp"
#include "components/LifeTime.hpp"
#include "components/Identity.hpp"
#include "components/AsteroidSize.hpp"

#include "events/AsteroidDestroyed.hpp"
#include "events/Victory.hpp"

#include <cmath>

using namespace CaptainAsteroidCPP::EntityHelper;

void AsteroidField::init(Def::InitParams initParams)
{
  m_nbMaxAsteroidsBySize = initParams.maxNbAsteroidsByType;

  m_nbAsteroidsXXL = initParams.initNbAsteroidsXXL;
  m_nbAsteroidsM = initParams.initNbAsteroidsM;
  m_nbAsteroidsS = initParams.initNbAsteroidsS;

  initFieldWithRandomPos(Comp::AstSize::XXL, initParams.boundaryDomainH, initParams.boundaryDomainV);
  initFieldWithRandomPos(Comp::AstSize::M, initParams.boundaryDomainH, initParams.boundaryDomainV);
  initFieldWithRandomPos(Comp::AstSize::S, initParams.boundaryDomainH, initParams.boundaryDomainV);

  // Empty field, nothing to do
  if (totalNbAsteroids() == 0)
  {
    m_eventManager.emit<Ev::Victory>();
  }
}

void AsteroidField::initFieldWithRandomPos(Comp::AstSize size, float boundaryH, float boundaryV)
{
  float radius = 0.0f;
  int nbAsteroids = 0;
  if (size == Comp::AstSize::XXL)
  {
    radius = m_radiusXXL;
    nbAsteroids = m_nbAsteroidsXXL;
  }
  else if (size == Comp::AstSize::M)
  {
    radius = m_radiusM;
    nbAsteroids = m_nbAsteroidsM;
  }
  else if (size == Comp::AstSize::S)
  {
    radius = m_radiusS;
    nbAsteroids = m_nbAsteroidsS;
  }

  for (size_t i = 0; i < nbAsteroids; ++i)
  {
    entityx::Entity asteroid = m_entityManager.create();
    asteroid.assign<Comp::Identity>(Comp::Id::Asteroid);
    asteroid.assign<Comp::AsteroidSize>(size);
    asteroid.assign<Comp::Motion>((rand() % 100) / 50.0f + 0.5f, 0);

    float randX = (rand() % 100) / 50.0f * boundaryH - boundaryH;
    float randY = (rand() % 100) / 50.0f * boundaryV - boundaryV;

    //Quick hack to avoid asteroid generation around space ship
    if (abs(randX) < 1.0f) randX += 4.0f;
    if (abs(randY) < 1.0f) randY += 4.0f;

    asteroid.assign<Comp::Position>(randX, randY, rand() % 360);
    asteroid.assign<Comp::Radius>(radius);
  }
}

void AsteroidField::createAsteroidsFromParent(entityx::Entity parent)
{
  if (parent.has_component<Comp::AsteroidSize>() && parent.has_component<Comp::Position>())
  {
    auto size = parent.component<Comp::AsteroidSize>()->size;
    float xParent = parent.component<Comp::Position>()->x;
    float yParent = parent.component<Comp::Position>()->y;

    if (size == Comp::AstSize::XXL && m_nbAsteroidsM < m_nbMaxAsteroidsBySize - 2)
    {
      entityx::Entity asteroid = m_entityManager.create();
      asteroid.assign<Comp::Identity>(Comp::Id::Asteroid);
      asteroid.assign<Comp::AsteroidSize>(Comp::AstSize::M);
      asteroid.assign<Comp::Motion>((rand() % 100) / 50.0f + 0.5f, 0);
      asteroid.assign<Comp::Position>(xParent + m_radiusM, yParent + m_radiusM, (float)(rand() % 360));
      asteroid.assign<Comp::Radius>(m_radiusM);

      asteroid = m_entityManager.create();
      asteroid.assign<Comp::Identity>(Comp::Id::Asteroid);
      asteroid.assign<Comp::AsteroidSize>(Comp::AstSize::M);
      asteroid.assign<Comp::Motion>((rand() % 100) / 50.0f + 0.5f, 0);
      asteroid.assign<Comp::Position>(xParent - m_radiusM, yParent - m_radiusM, (float)(rand() % 360));
      asteroid.assign<Comp::Radius>(m_radiusM);

      m_nbAsteroidsM += 2;
    }
    else if (size == Comp::AstSize::M && m_nbAsteroidsS < m_nbMaxAsteroidsBySize - 2)
    {
      entityx::Entity asteroid = m_entityManager.create();
      asteroid.assign<Comp::Identity>(Comp::Id::Asteroid);
      asteroid.assign<Comp::AsteroidSize>(Comp::AstSize::S);
      asteroid.assign<Comp::Motion>((rand() % 100) / 50.0f + 0.5f, 0);
      asteroid.assign<Comp::Position>(xParent + m_radiusS, yParent + m_radiusS, (float)(rand() % 360));
      asteroid.assign<Comp::Radius>(m_radiusS);

      asteroid = m_entityManager.create();
      asteroid.assign<Comp::Identity>(Comp::Id::Asteroid);
      asteroid.assign<Comp::AsteroidSize>(Comp::AstSize::S);
      asteroid.assign<Comp::Motion>((rand() % 100) / 50.0f + 0.5f, 0);
      asteroid.assign<Comp::Position>(xParent - m_radiusS, yParent - m_radiusS, (float)(rand() % 360));
      asteroid.assign<Comp::Radius>(m_radiusS);

      m_nbAsteroidsS += 2;
    }
  }
}

void AsteroidField::destroyAsteroid(entityx::Entity asteroid)
{
  if (asteroid.has_component<Comp::AsteroidSize>())
  {
    auto size = asteroid.component<Comp::AsteroidSize>()->size;

    if (size == Comp::AstSize::XXL)
    {
      m_nbAsteroidsXXL--;
    }
    else if (size == Comp::AstSize::M)
    {
      m_nbAsteroidsM--;
    }
    else if (size == Comp::AstSize::S)
    {
      m_nbAsteroidsS--;
    }

    m_eventManager.emit<Ev::AsteroidDestroyed>(size);

    if (totalNbAsteroids() == 0)
    {
      m_eventManager.emit<Ev::Victory>();
    }

    asteroid.destroy();
  }
}

void AsteroidField::fillPosEntityList(float *posEntities, int sizeBuffer, int *nbEntities, Def::EntityType entityType) const
{
  int nbAsteroids = 0;
  auto selSize = Comp::AstSize::Unknown;
  if (entityType == Def::EntityType::Asteroid_XXL)
  {
    selSize = Comp::AstSize::XXL;
    nbAsteroids = m_nbAsteroidsXXL;
  }
  else if (entityType == Def::EntityType::Asteroid_M)
  {
    selSize = Comp::AstSize::M;
    nbAsteroids = m_nbAsteroidsM;
  }
  else if (entityType == Def::EntityType::Asteroid_S)
  {
    selSize = Comp::AstSize::S;
    nbAsteroids = m_nbAsteroidsS;
  }

  Comp::Position::Handle position;
  Comp::Identity::Handle identity;
  Comp::AsteroidSize::Handle asteroidSize;

  size_t i = 0;
  for (entityx::Entity entity : m_entityManager.entities_with_components(position, identity, asteroidSize))
  {
    if (identity->id != Comp::Id::Asteroid || asteroidSize->size != selSize) continue;

    if (i < sizeBuffer)
    {
      posEntities[i++] = position->x;
      posEntities[i++] = position->y;
      posEntities[i++] = position->angle;
    }
  }

  *nbEntities = (int)nbAsteroids;
}