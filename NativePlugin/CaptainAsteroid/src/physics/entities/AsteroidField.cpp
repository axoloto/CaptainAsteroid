#include "AsteroidField.hpp"

#include "Utils.hpp"

#include "components/MotionC.hpp"
#include "components/PositionC.hpp"

using namespace AsteroidsCPP;

void AsteroidField::init(int nbAsteroids)
{
  m_nbAsteroids = nbAsteroids;

  for (int i = 0; i < m_nbAsteroids; ++i)
  {
    entityx::Entity asteroid = m_entityManager.create();
    asteroid.assign<MotionC>(rand() % 5, 0);
    asteroid.assign<PositionC>(rand() % 10, rand() % 12, rand() % 360);
  }
}

void AsteroidField::fillPosEntityList(float *posEntities, int size, int *nbEntities, Utils::EntityType entityType)
{
  PositionC::Handle position;

  int i = 0;
  for (entityx::Entity entity : m_entityManager.entities_with_components(position))//bug wip
  {
    if (i >= size) break;// Should not happen
    posEntities[i++] = position->x;
    posEntities[i++] = position->y;
    posEntities[i++] = position->angle;
  }

  *nbEntities = m_nbAsteroids;
}