#ifndef TILEINFO_H
#define TILEINFO_H

#include <eigen3/Eigen/Geometry>
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
