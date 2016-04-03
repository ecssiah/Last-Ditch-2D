#ifndef TILEINFO_H
#define TILEINFO_H

#include <eigen3/Eigen/Geometry>
#include <SDL2/SDL.h>
#include <string>

namespace ld
{

struct TileInfo
{
  TileInfo() = default;

  std::string texture;
  SDL_Rect clip_rect;
};

}

#endif /* TILEINFO_H */
