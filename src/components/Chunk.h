#ifndef CHUNK_H
#define CHUNK_H

#include <eigen3/Eigen/Geometry>
#include <SDL2/SDL.h>
#include <vector>

#include "Tile.h"

namespace ld
{

struct Chunk
{
  Chunk()
    : type("chunk_floor1"),
      pos(0, 0),
      tiles(TILES_PER_CHUNK_X, {TILES_PER_CHUNK_Y, Tile()})
  {}

  std::string type;
  Eigen::Vector2i pos;
  std::vector<std::vector<Tile>> tiles;
};

}

#endif /* CHUNK_H */
