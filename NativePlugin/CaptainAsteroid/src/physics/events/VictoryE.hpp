#pragma once

#include "entityx/Event.h"
#include "entityx/Entity.h"

#include "utils.hpp"

namespace AsteroidsCPP
{
struct VictoryE : public entityx::Event<VictoryE>
{
  VictoryE(){};
};
}// namespace AsteroidsCPP