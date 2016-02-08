#ifndef CHUNK_H
#define CHUNK_H

#include <eigen3/Eigen/Geometry>
#include <SDL2/SDL.h>
#include <vector>

#include "Item.h"
#include "StaticEntity.h"

namespace ld
{

struct Chunk : public StaticEntity
{
  Chunk()
    : StaticEntity(),
      entities(TILES_PER_CHUNK_X, {TILES_PER_CHUNK_Y, StaticEntity()}),
      floor_entities(TILES_PER_CHUNK_X, {TILES_PER_CHUNK_Y, StaticEntity()}),
      items()
  {
    texture_name = "chunk_floor1";
  }

  std::vector<std::vector<StaticEntity>> entities;
  std::vector<std::vector<StaticEntity>> floor_entities;

  std::vector<Item> items;
};

}

#endif /* CHUNK_H */
