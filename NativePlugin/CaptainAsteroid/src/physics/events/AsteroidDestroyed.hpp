#pragma once

#include "entityx/Event.h"
#include "entityx/Entity.h"

#include "components/AsteroidSize.hpp"

namespace CaptainAsteroidCPP
{
namespace Ev
{
  struct AsteroidDestroyed : public entityx::Event<AsteroidDestroyed>
  {
    AsteroidDestroyed(Comp::AstSize _type) : type(_type){};

    Comp::AstSize type;
  };
}// namespace Ev
}// namespace CaptainAsteroidCPP