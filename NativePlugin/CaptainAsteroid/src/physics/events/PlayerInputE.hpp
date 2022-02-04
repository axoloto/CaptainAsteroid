#pragma once

#include "entityx/Event.h"
#include "entityx/Entity.h"

#include "utils.hpp"

namespace AsteroidsCPP
{
struct PlayerInputE : public entityx::Event<PlayerInputE>
{
  PlayerInputE(const Utils::KeyState &state) : keyState(state){};

  Utils::KeyState keyState;
};
}// namespace AsteroidsCPP