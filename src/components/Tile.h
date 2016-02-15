#ifndef TILE_H
#define TILE_H

#include <Box2D/Box2D.h>

#include "Entity.h"

namespace ld
{

struct Tile : public Entity
{
  Tile()
    : rotation(0.f),
      solid(false),
      body(nullptr)
  {}

  float rotation;
  bool solid;

  b2Body* body;
};

}

#endif /* TILE_H */
