#ifndef CHUNK_H
#define CHUNK_H

#include <eigen3/Eigen/Geometry>
#include <SDL2/SDL.h>
#include <vector>

#include "Door.h"
#include "Item.h"
#include "Tile.h"
#include "../constants/MapConstants.h"

namespace ld
{

struct Chunk : public Entity
{
  Chunk()
    : Entity(),
      main_tiles(TILES_PER_CHUNK_X, {TILES_PER_CHUNK_Y, Tile()}),
      floor_tiles(TILES_PER_CHUNK_X, {TILES_PER_CHUNK_Y, Tile()}),
      items(),
      doors()
  {
    size = {TILES_PER_CHUNK_X, TILES_PER_CHUNK_Y};
  }

  std::vector<std::vector<Tile>> main_tiles;
  std::vector<std::vector<Tile>> floor_tiles;

  std::vector<Item> items;
  std::vector<Door> doors;
};

}

#endif /* CHUNK_H */
