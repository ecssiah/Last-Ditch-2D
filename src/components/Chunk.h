#ifndef CHUNK_H
#define CHUNK_H

#include <eigen3/Eigen/Geometry>
#include <vector>

#include "Tile.h"

struct Chunk
{
  Chunk()
    : pos(0, 0),
      tiles()
  {}

  Eigen::Vector2i pos;
  std::vector<Tile> tiles;
};

#endif /* CHUNK_H */
