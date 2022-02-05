#pragma once

#include "entityx/Event.h"
#include "entityx/Entity.h"

#include "components/AsteroidTypeC.hpp"

namespace AsteroidsCPP
{
struct AsteroidDestroyedE : public entityx::Event<AsteroidDestroyedE>
{
  AsteroidDestroyedE(Type _type) : type(_type){};

  Type type;
};
}// namespace AsteroidsCPP