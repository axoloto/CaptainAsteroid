#include "AsteroidField.hpp"

#include "Utils.hpp"

#include "components/SizeC.hpp"
#include "components/MotionC.hpp"
#include "components/PositionC.hpp"
#include "components/PlayerControlC.hpp"
#include "components/LifeTimeC.hpp"

using namespace AsteroidsCPP;

void AsteroidField::init(int nbAsteroids, float boundaryV, float boundaryH)
{
  m_nbAsteroids = nbAsteroids;

  for (int i = 0; i < m_nbAsteroids; ++i)
  {
    entityx::Entity asteroid = m_entityManager.create();
    asteroid.assign<MotionC>(rand() % 8, 0);

    float randX = (rand() % 10) / 5.0f * boundaryH - boundaryH;
    float randY = (rand() % 10) / 5.0f * boundaryV - boundaryV;
    asteroid.assign<PositionC>(randX, randY, rand() % 360);

    asteroid.assign<SizeC>(1.0f);
  }
}

void AsteroidField::fillPosEntityList(float *posEntities, int size, int *nbEntities, Utils::EntityType entityType)
{
  PositionC::Handle position;

  int i = 0;
  for (entityx::Entity entity : m_entityManager.entities_with_components(position))
  {
    if (i >= size) break;// Should not happen
    if (entity.has_component<PlayerControlC>() || entity.has_component<LifeTimeC>()) continue;

    posEntities[i++] = position->x;
    posEntities[i++] = position->y;
    posEntities[i++] = position->angle;
  }

  *nbEntities = i / 3;
}