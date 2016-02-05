#ifndef TILE_H
#define TILE_H

#include <Box2D/Box2D.h>
#include <eigen3/Eigen/Geometry>
#include <string>

struct Tile
{
  Tile()
    : type(std::string()),
      pos(0, 0),
      solid(false),
      rotation(0.0),
      body(nullptr),
      update(false)
  {}

  std::string type;
  Eigen::Vector2i pos;
  bool solid;
  double rotation;
  b2Body* body;
  bool update;
};

#endif /* TILE_H */
