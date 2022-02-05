#pragma once

#include "entityx/Event.h"
#include "entityx/Entity.h"

namespace CaptainAsteroidCPP
{
struct GameOverE : public entityx::Event<GameOverE>
{
  GameOverE(){};
};
}// namespace CaptainAsteroidCPP