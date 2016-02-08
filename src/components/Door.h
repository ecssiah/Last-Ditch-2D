#ifndef DOOR_H
#define DOOR_H

#include <eigen3/Eigen/Geometry>

#include "Entity.h"

namespace ld
{

struct Door : public Entity
{
  Door() = default;

  Door(float x, float y)
    : Entity(),
      open(false),
      locked(false)
  {
    pos = {x, y};
  }

  bool open, locked;
};

}

#endif /* DOOR_H */
