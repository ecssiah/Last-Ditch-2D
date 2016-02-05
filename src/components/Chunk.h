#ifndef CHUNK_H
#define CHUNK_H

#include <eigen3/Eigen/Geometry>
#include <SDL2/SDL.h>
#include <vector>

#include "Tile.h"
#include "StaticEntity.h"

namespace ld
{

struct Chunk
{
  Chunk()
    : type("chunk_floor1"),
      pos(0, 0),
      tiles(TILES_PER_CHUNK_X, {TILES_PER_CHUNK_Y, Tile()}),
      floor_tiles(TILES_PER_CHUNK_X, {TILES_PER_CHUNK_Y, Tile()}),
      items(),
      update(false)
  {}

  std::string type;
  Eigen::Vector2i pos;
  std::vector<std::vector<Tile>> tiles;
  std::vector<std::vector<Tile>> floor_tiles;
  std::vector<StaticEntity> items;
  bool update;
};

}

#endif /* CHUNK_H */
