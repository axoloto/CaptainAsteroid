#include "SpaceShip.hpp"

#include "Utils.hpp"

#include "components/SizeC.hpp"
#include "components/MotionC.hpp"
#include "components/PositionC.hpp"
#include "components/PlayerControlC.hpp"
#include "components/LaserC.hpp"

using namespace AsteroidsCPP;

void SpaceShip::init()
{
  entityx::Entity spaceShip = m_entityManager.create();
  spaceShip.assign<MotionC>();
  spaceShip.assign<PositionC>();
  spaceShip.assign<LaserC>();
  spaceShip.assign<PlayerControlC>();
  spaceShip.assign<SizeC>(0.5f);
}

std::array<float, 3> SpaceShip::getPosAndDir()
{
  // WIP
  PlayerControlC::Handle playerControl;
  PositionC::Handle position;
  std::array<float, 3> coordsAndRot = { 0, 0, 0 };
  for (entityx::Entity entity : m_entityManager.entities_with_components(playerControl, position))
  {
    coordsAndRot = { position->x, position->y, position->angle };
  }

  return coordsAndRot;
}
