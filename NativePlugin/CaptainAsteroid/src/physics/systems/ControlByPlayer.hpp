#pragma once

#include "entityx/System.h"
#include "entityx/Event.h"

#include "events/PlayerInput.hpp"
#include "Define.hpp"

namespace CaptainAsteroidCPP
{
namespace Sys
{
  class ControlByPlayer : public entityx::System<ControlByPlayer>
    , public entityx::Receiver<Ev::PlayerInput>
  {
  public:
    ControlByPlayer();

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
