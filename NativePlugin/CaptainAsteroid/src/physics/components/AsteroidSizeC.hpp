#pragma once

#include "entityx/Entity.h"

namespace CaptainAsteroidCPP
{
enum class AstSize
{
  Unknown,
  XXL,
  M,
  S
};

struct AsteroidSizeC : public entityx::Component<AsteroidSizeC>
{
  AsteroidSizeC(AstSize _type = AstSize::XXL) : type(_type){};

  AstSize type;
};
}// namespace CaptainAsteroidCPP