#pragma once

#include "entityx/System.h"
#include "entityx/Event.h"

#include "events/PlayerInput.hpp"
#include "Define.hpp"

namespace CaptainAsteroidCPP
{
namespace Sys
{
  class PlayerControl : public entityx::System<PlayerControl>
    , public entityx::Receiver<Ev::PlayerInput>
  {
  public:
    PlayerControl();

    void update(entityx::EntityManager &entities,
      entityx::EventManager &events,
      double dt) override;

    void configure(entityx::EventManager &eventManager);
    void receive(const Ev::PlayerInput &event);

  private:
    Def::KeyState m_keyState;
  };
}// namespace Sys
}// namespace CaptainAsteroidCPP
