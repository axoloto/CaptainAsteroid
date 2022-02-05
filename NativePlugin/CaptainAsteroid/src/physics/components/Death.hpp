#pragma once

#include "entityx/Entity.h"

namespace CaptainAsteroidCPP
{
namespace Comp
{
  struct Death : public entityx::Component<Death>
  {
    Death(){};
  };
}// namespace Comp
}// namespace CaptainAsteroidCPP