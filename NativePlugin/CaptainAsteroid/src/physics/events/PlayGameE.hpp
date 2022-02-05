#pragma once

#include "entityx/Event.h"
#include "entityx/Entity.h"

namespace CaptainAsteroidCPP
{
struct PlayGameE : public entityx::Event<PlayGameE>
{
  PlayGameE(){};
};
}// namespace CaptainAsteroidCPP