#pragma once

#include "entityx/Event.h"
#include "entityx/Entity.h"

#include "Define.hpp"

namespace CaptainAsteroidCPP
{
namespace Ev
{
  struct PlayerInput : public entityx::Event<PlayerInput>
  {
    PlayerInput(const Def::KeyState &state) : keyState(state){};

    Def::KeyState keyState;
  };
}// namespace Ev
}// namespace CaptainAsteroidCPP