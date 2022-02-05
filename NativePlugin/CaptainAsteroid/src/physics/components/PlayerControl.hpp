#pragma once

#include "entityx/Entity.h"
namespace CaptainAsteroidCPP
{
namespace Comp
{
  struct PlayerControl : public entityx::Component<PlayerControl>
  {
    PlayerControl(){};
  };
}// namespace Comp
}// namespace CaptainAsteroidCPP