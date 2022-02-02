#pragma once

#include "entityx/System.h"

class MovementS : public entityx::System<MovementS>
{
  MovementS(int width, int height) : width(width), height(height) {}

  void update(entityx::EntityManager &entities,
    entityx::EventManager &events,
    double dt);

private:
  int width, height;
};