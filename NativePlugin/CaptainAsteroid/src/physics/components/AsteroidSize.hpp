#pragma once

#include "entityx/Entity.h"

namespace CaptainAsteroidCPP
{
namespace Comp
{
  enum class AstSize
  {
    Unknown,
    XXL,
    M,
    S
  };

  struct AsteroidSize : public entityx::Component<AsteroidSize>
  {
    AsteroidSize(AstSize _size = AstSize::XXL) : size(_size){};

    AstSize size;
  };
}// namespace Comp
}// namespace CaptainAsteroidCPP