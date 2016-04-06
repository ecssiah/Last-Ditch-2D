#ifndef TILE_H
#define TILE_H

#include <Box2D/Box2D.h>

#include "Entity.h"

namespace ld
{

struct Tile : public Entity
{
  Tile()
    : solid(false),
      direction(0),
      body(nullptr)
  {}

  bool solid;
  unsigned direction;

  b2Body* body;
};

}

#endif /* TILE_H */
