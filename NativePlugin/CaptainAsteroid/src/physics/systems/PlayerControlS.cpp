#include "PlayerControlS.hpp"

#include "components/MotionC.hpp"
#include "components/LaserC.hpp"
#include "components/PlayerControlC.hpp"

#include <algorithm>
#include <cmath>

using namespace AsteroidsCPP;

PlayerControlS::PlayerControlS(){};

void PlayerControlS::update(
  entityx::EntityManager &entities,
  entityx::EventManager &events,
  double dt)
{
  constexpr float maxSpeed = 0.05f;
  constexpr float thrustCoeff = 1.0f;
  constexpr float angleCoeff = 0.7f;
  constexpr float frictionCoeff = 0.99f;

  MotionC::Handle motion;
  LaserC::Handle laser;
  PlayerControlC::Handle playerControl;
  for (entityx::Entity entity : entities.entities_with_components(playerControl, motion, laser))
  {
    if (m_keyState.pressed(Utils::KeyState::Keys::Down))
    {
      motion->acc -= thrustCoeff;
    }
    if (m_keyState.pressed(Utils::KeyState::Keys::Up))
    {
      motion->acc += thrustCoeff;
    }
    motion->acc *= frictionCoeff;

    motion->rot = 0.0f;
    if (m_keyState.pressed(Utils::KeyState::Keys::Left))
    {
      motion->rot = angleCoeff;
    }
    if (m_keyState.pressed(Utils::KeyState::Keys::Right))
    {
      motion->rot = -angleCoeff;
    }

    motion->vel += std::max(0.0f, std::min(motion->acc * (float)dt, maxSpeed));
    motion->vel *= frictionCoeff;

    //gun->isMainFirePressed = m_keyHandler.isPressed(playerControl->shoot);
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
