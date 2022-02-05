#pragma once

#include "entityx/Event.h"
#include "entityx/Entity.h"

namespace CaptainAsteroidCPP
{
namespace Ev
{
  struct GameOver : public entityx::Event<GameOver>
  {
    GameOver(){};
  };
}// namespace Ev
}// namespace CaptainAsteroidCPP