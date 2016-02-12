#ifndef DOOR_H
#define DOOR_H

#include <eigen3/Eigen/Geometry>

#include "Entity.h"

namespace ld
{

struct Door : public Entity
{
  Door()
    : Entity(),
      open(false),
      locked(false)
  {
    type = "door";
  }

  Door(float x, float y)
    : Entity(),
      open(false),
      locked(false)
  {
    type = "door";
    pos = {x, y};
  }

  bool open, locked;
};

}

#endif /* DOOR_H */
