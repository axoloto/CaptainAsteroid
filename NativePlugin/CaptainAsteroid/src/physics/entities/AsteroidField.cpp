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

void AsteroidField::init(int nbAsteroids, float boundaryV, float boundaryH)
{
  m_nbAsteroids = nbAsteroids;

  for (int i = 0; i < m_nbAsteroids; ++i)
  {
    entityx::Entity asteroid = m_entityManager.create();
    asteroid.assign<IdentityC>(Id::Asteroid);
    asteroid.assign<AsteroidTypeC>(Type::XXL);
    asteroid.assign<MotionC>((rand() % 100) / 30.0f + 0.5f, 0);

    float randX = (rand() % 100) / 50.0f * boundaryH - boundaryH;
    float randY = (rand() % 100) / 50.0f * boundaryV - boundaryV;

    //Quick hack to avoid asteroid generation around space ship
    if (abs(randX) < 1.0f) randX += 4.0f;
    if (abs(randY) < 1.0f) randY += 4.0f;

    asteroid.assign<PositionC>(randX, randY, rand() % 360);
    asteroid.assign<RadiusC>(0.55f);
  }
}

void AsteroidField::removeAsteroid(entityx::Entity asteroid)
{
  asteroid.destroy();
  m_nbAsteroids--;
}

void AsteroidField::fillPosEntityList(float *posEntities, int size, int *nbEntities, Utils::EntityType entityType)
{
  PositionC::Handle position;
  IdentityC::Handle identity;

  int i = 0;
  for (entityx::Entity entity : m_entityManager.entities_with_components(position, identity))
  {
    if (i >= size) break;// Should not happen
    if (identity->id != Id::Asteroid) continue;// TODO

    posEntities[i++] = position->x;
    posEntities[i++] = position->y;
    posEntities[i++] = position->angle;
  }

  *nbEntities = m_nbAsteroids;
}