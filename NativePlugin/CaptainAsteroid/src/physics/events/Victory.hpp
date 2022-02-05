#pragma once

#include "entityx/Event.h"
#include "entityx/Entity.h"

namespace CaptainAsteroidCPP
{
namespace Ev
{
  struct Victory : public entityx::Event<Victory>
  {
    Victory(){};
  };
}// namespace Ev
}// namespace CaptainAsteroidCPP