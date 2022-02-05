#pragma once

#include "entityx/Entity.h"

namespace CaptainAsteroidCPP
{
namespace Comp
{
  struct AsteroidParent : public entityx::Component<AsteroidParent>
  {
    AsteroidParent(){};
  };
}// namespace Comp
}// namespace CaptainAsteroidCPP