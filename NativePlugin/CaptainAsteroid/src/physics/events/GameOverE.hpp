#pragma once

#include "entityx/Event.h"
#include "entityx/Entity.h"

namespace AsteroidsCPP
{
struct GameOverE : public entityx::Event<GameOverE>
{
  GameOverE(){};
};
}// namespace AsteroidsCPP