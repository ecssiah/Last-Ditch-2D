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
      direction(0),
      solid(true),
      open(false),
      locked(false),
      body(nullptr)
  {}

  unsigned direction;
  bool solid;
  bool open;
  bool locked;

  b2Body* body;
};

}

#endif /* DOOR_H */
