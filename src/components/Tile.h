#ifndef TILE_H
#define TILE_H

#include <string>

struct Tile
{
  Tile()
    : type(""),
      solid(false),
      rotation(0.0)
  {}

  std::string type;
  bool solid;
  double rotation;
};

#endif /* TILE_H */
