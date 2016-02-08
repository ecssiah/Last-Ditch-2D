#ifndef CHUNK_H
#define CHUNK_H

#include <eigen3/Eigen/Geometry>
#include <SDL2/SDL.h>
#include <vector>

#include "Item.h"
#include "Entity.h"

namespace ld
{

struct Chunk : public Entity
{
  Chunk()
    : Entity(),
      entities(TILES_PER_CHUNK_X, {TILES_PER_CHUNK_Y, Entity()}),
      floor_entities(TILES_PER_CHUNK_X, {TILES_PER_CHUNK_Y, Entity()}),
      items()
  {
    texture_name = "chunk_floor1";
  }

  std::vector<std::vector<Entity>> entities;
  std::vector<std::vector<Entity>> floor_entities;

  std::vector<Item> items;
};

}

#endif /* CHUNK_H */
