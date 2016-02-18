#ifndef DOOR_H
#define DOOR_H

#include <Box2D/Box2D.h>
#include <eigen3/Eigen/Geometry>

#include "Entity.h"

namespace ld
{

struct Door : public Entity
{
  Door()
    : Entity(),
      rotation(0.f),
      solid(true),
      open(false),
      locked(false),
      body(nullptr)
  {}

  Door(float x, float y)
    : Entity(),
      solid(true),
      open(false),
      locked(false),
      body(nullptr)
  {
    pos = {x, y};
  }

  float rotation;
  bool solid;
  bool open, locked;

  b2Body* body;
};

}

#endif /* DOOR_H */
