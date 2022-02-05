#pragma once

#include "entityx/Event.h"
#include "entityx/Entity.h"

namespace AsteroidsCPP
{
struct PlayGameE : public entityx::Event<PlayGameE>
{
  PlayGameE(){};
};
}// namespace AsteroidsCPP