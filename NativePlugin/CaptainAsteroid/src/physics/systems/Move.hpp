#pragma once

#include "entityx/System.h"

namespace CaptainAsteroidCPP
{
namespace Sys
{
  class Move : public entityx::System<Move>
  {
  public:
    Move(float boundaryV, float boundaryH) : m_boundaryV(boundaryV), m_boundaryH(boundaryH){};

    void update(entityx::EntityManager &entities,
      entityx::EventManager &events,
      double dt);

  private:
    float m_boundaryV, m_boundaryH;
  };
}// namespace Sys
}// namespace CaptainAsteroidCPP