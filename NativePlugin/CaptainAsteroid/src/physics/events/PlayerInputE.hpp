#pragma once

#include "entityx/Event.h"
#include "entityx/Entity.h"

#include "Define.hpp"

namespace CaptainAsteroidCPP
{
struct PlayerInputE : public entityx::Event<PlayerInputE>
{
  PlayerInputE(const Def::KeyState &state) : keyState(state){};

  Def::KeyState keyState;
};
}// namespace CaptainAsteroidCPP