#ifndef TILE_H
#define TILE_H

#include <eigen3/Eigen/Geometry>
#include <string>

struct Tile
{
  Tile()
    : type(std::string()),
      pos(0, 0),
      solid(false),
      rotation(0.0)
  {}

  std::string type;
  Eigen::Vector2i pos;
  bool solid;
  double rotation;
};

#endif /* TILE_H */
