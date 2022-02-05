#include "PlayerControlS.hpp"

#include "components/MotionC.hpp"
#include "components/LaserC.hpp"
#include "components/PlayerControlC.hpp"

#include <algorithm>
#include <cmath>

using namespace CaptainAsteroidCPP;

PlayerControlS::PlayerControlS(){};

void PlayerControlS::update(
  entityx::EntityManager &entities,
  entityx::EventManager &events,
  double dt)
{
  constexpr float maxAcc = 0.05f;
  constexpr float thrustCoeff = 20.0f;
  constexpr float angleCoeff = 1.2f;
  constexpr float frictionCoeff = 0.997f;

  MotionC::Handle motion;
  LaserC::Handle laser;
  PlayerControlC::Handle playerControl;
  for (entityx::Entity entity : entities.entities_with_components(playerControl, motion, laser))
  {
    float acc = 0.0f;
    if (m_keyState.pressed(Def::KeyState::Keys::Down))//use playerControl
    {
      acc = -thrustCoeff;
    }
    if (m_keyState.pressed(Def::KeyState::Keys::Up))
    {
      acc = thrustCoeff;
    }

    motion->rot = 0.0f;
    if (m_keyState.pressed(Def::KeyState::Keys::Left))
    {
      motion->rot = angleCoeff;
    }
    if (m_keyState.pressed(Def::KeyState::Keys::Right))
    {
      motion->rot = -angleCoeff;
    }

    motion->vel += acc * (float)dt;
    motion->vel *= frictionCoeff;
    motion->vel = std::max(0.0f, std::min(motion->vel, 20.0f));

    laser->isFiring = m_keyState.pressed(Def::KeyState::Keys::Space);
  }
}

void PlayerControlS::configure(entityx::EventManager &eventManager)
{
  eventManager.subscribe<PlayerInputE>(*this);
}

void PlayerControlS::receive(const PlayerInputE &event)
{
  m_keyState = event.keyState;
}
