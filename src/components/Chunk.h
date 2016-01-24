#ifndef CHUNK_H
#define CHUNK_H

#include <eigen3/Eigen/Geometry>
#include <SDL2/SDL.h>
#include <vector>

#include "Tile.h"

struct Chunk
{
  Chunk()
    : type("chunk_floor1"),
      pos(0, 0),
      tiles(),
      dest_rect()
  {
    dest_rect.x = 0;
    dest_rect.y = 0;
    dest_rect.w = 920;
    dest_rect.h = 920;
  }

  std::string type;
  Eigen::Vector2i pos;
  std::vector<Tile> tiles;
  SDL_Rect dest_rect;
};

#endif /* CHUNK_H */
