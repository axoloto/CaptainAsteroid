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
    asteroid.assign<MotionC>();
    asteroid.assign<PositionC>();
  }
}

std::array<float, 2> AsteroidField::getCoords()
{
  // WIP
  PositionC::Handle position;
  MotionC::Handle motion;
  std::array<float, 2> coords = { 0, 0 };
  for (entityx::Entity entity : m_entityManager.entities_with_components(position, motion))
  {
    // coordsAndRot = { position->x, position->y, motion->rot };
  }

  return coords;
}
