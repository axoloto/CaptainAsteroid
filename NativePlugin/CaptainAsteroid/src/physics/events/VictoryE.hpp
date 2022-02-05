#pragma once

#include "entityx/Event.h"
#include "entityx/Entity.h"

namespace CaptainAsteroidCPP
{
struct VictoryE : public entityx::Event<VictoryE>
{
  VictoryE(){};
};
}// namespace CaptainAsteroidCPP