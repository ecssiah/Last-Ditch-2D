#ifndef TILE_H
#define TILE_H

#include <Box2D/Box2D.h>
#include <eigen3/Eigen/Geometry>
#include <string>

#include "StaticEntity.h"

namespace ld
{

struct Tile : public StaticEntity
{
  Tile()
    : StaticEntity(),
      solid(false),
      rotation(0.f)
  {}

  bool solid;
  float rotation;
};

}

#endif /* TILE_H */
