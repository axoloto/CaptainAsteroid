#pragma once

#include "entityx/System.h"
#include "entityx/Event.h"

#include "events/PlayerInputE.hpp"
#include "Define.hpp"

namespace CaptainAsteroidCPP
{
class PlayerControlS : public entityx::System<PlayerControlS>
  , public entityx::Receiver<PlayerInputE>
{
public:
  PlayerControlS();

  void update(entityx::EntityManager &entities,
    entityx::EventManager &events,
    double dt) override;

  void configure(entityx::EventManager &eventManager);
  void receive(const PlayerInputE &event);

private:
  Def::KeyState m_keyState;
};
}// namespace CaptainAsteroidCPP
