#ifndef DOOR_H
#define DOOR_H

#include <eigen3/Eigen/Geometry>

#include "StaticEntity.h"

namespace ld
{

struct Door : public StaticEntity
{
  Door(float x, float y)
    : open(false),
      locked(false)
  {
    pos = {x, y};
  }

  bool open, locked;
};

}

#endif /* DOOR_H */
