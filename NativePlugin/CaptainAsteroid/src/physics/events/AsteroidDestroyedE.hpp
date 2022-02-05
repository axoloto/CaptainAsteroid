#pragma once

#include "entityx/Event.h"
#include "entityx/Entity.h"

#include "components/AsteroidSizeC.hpp"

namespace AsteroidsCPP
{
struct AsteroidDestroyedE : public entityx::Event<AsteroidDestroyedE>
{
  AsteroidDestroyedE(AstSize _type) : type(_type){};

  AstSize type;
};
}// namespace AsteroidsCPP