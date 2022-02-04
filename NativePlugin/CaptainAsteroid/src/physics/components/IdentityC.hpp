#pragma once

#include "entityx/Entity.h"

namespace AsteroidsCPP
{
enum class Id
{
  Unknown,
  Asteroid,
  SpaceShip,
  LaserShot
};

struct IdentityC : public entityx::Component<IdentityC>
{
  IdentityC(Id _id = Id::Unknown) : id(_id){};

  Id id;
};
}// namespace AsteroidsCPP