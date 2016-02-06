#ifndef DOOR_H
#define DOOR_H

#include <eigen3/Eigen/Geometry>

struct Door
{
  Door(float x, float y)
    : open(false),
      locked(false),
      pos(x, y)
  {}

  Eigen::Vector2f pos;
  bool open, locked;
};

#endif /* DOOR_H */
