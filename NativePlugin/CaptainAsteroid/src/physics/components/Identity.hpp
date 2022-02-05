#pragma once

#include "entityx/Entity.h"

namespace CaptainAsteroidCPP
{
namespace Comp
{
  enum class Id
  {
    Unknown,
    Asteroid,
    SpaceShip,
    LaserShot
  };

  struct Identity : public entityx::Component<Identity>
  {
    Identity(Id _id = Id::Unknown) : id(_id){};

    Id id;
  };
}// namespace Comp
}// namespace CaptainAsteroidCPP