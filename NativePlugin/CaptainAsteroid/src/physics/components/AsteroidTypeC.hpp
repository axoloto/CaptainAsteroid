#pragma once

#include "entityx/Entity.h"

namespace AsteroidsCPP
{
enum class Type
{
  Unknown,
  XXL,
  M,
  S
};

struct AsteroidTypeC : public entityx::Component<AsteroidTypeC>
{
  AsteroidTypeC(Type _type = Type::XXL) : type(_type){};

  Type type;
};
}// namespace AsteroidsCPP