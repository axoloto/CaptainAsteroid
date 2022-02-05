#include "SpaceShip.hpp"

#include "Define.hpp"

#include "components/Radius.hpp"
#include "components/Motion.hpp"
#include "components/Position.hpp"
#include "components/PlayerControl.hpp"
#include "components/Laser.hpp"
#include "components/Identity.hpp"

using namespace CaptainAsteroidCPP::EntityHelper;

void SpaceShip::init()
{
  entityx::Entity spaceShip = m_entityManager.create();
  spaceShip.assign<Comp::Identity>(Comp::Id::SpaceShip);
  spaceShip.assign<Comp::Motion>();
  spaceShip.assign<Comp::Position>();
  spaceShip.assign<Comp::Laser>();
  spaceShip.assign<Comp::PlayerControl>();
  spaceShip.assign<Comp::Radius>(0.3f);
}

std::array<float, 3> SpaceShip::getPosAndDir() const
{
  Comp::Position::Handle position;
  Comp::PlayerControl::Handle playerControl;
  std::array<float, 3> coordsAndRot = { 0, 0, 0 };
  for (entityx::Entity entity : m_entityManager.entities_with_components(playerControl, position))
  {
    coordsAndRot = { position->x, position->y, position->angle };
    break;
  }

  return coordsAndRot;
}
