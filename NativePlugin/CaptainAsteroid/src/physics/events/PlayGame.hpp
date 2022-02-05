#pragma once

#include "entityx/Event.h"
#include "entityx/Entity.h"

namespace CaptainAsteroidCPP
{
namespace Ev
{
  struct PlayGame : public entityx::Event<PlayGame>
  {
    PlayGame(){};
  };
}// namespace Ev
}// namespace CaptainAsteroidCPP