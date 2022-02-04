#include "SpaceShip.hpp"

#include "Utils.hpp"

#include "components/RadiusC.hpp"
#include "components/MotionC.hpp"
#include "components/PositionC.hpp"
#include "components/PlayerControlC.hpp"
#include "components/LaserC.hpp"
#include "components/IdentityC.hpp"

using namespace AsteroidsCPP;

void SpaceShip::init()
{
  entityx::Entity spaceShip = m_entityManager.create();
  spaceShip.assign<IdentityC>(Id::SpaceShip);
  spaceShip.assign<MotionC>();
  spaceShip.assign<PositionC>();
  spaceShip.assign<LaserC>();
  spaceShip.assign<PlayerControlC>();
  spaceShip.assign<RadiusC>(0.3f);
}

std::array<float, 3> SpaceShip::getPosAndDir() const
{
  PositionC::Handle position;
  PlayerControlC::Handle playerControl;
  std::array<float, 3> coordsAndRot = { 0, 0, 0 };
  for (entityx::Entity entity : m_entityManager.entities_with_components(playerControl, position))
  {
    coordsAndRot = { position->x, position->y, position->angle };
    break;
  }

  return coordsAndRot;
}
