#ifndef ENTITY_H
#define ENTITY_H

#include <eigen3/Eigen/Geometry>
#include <string>

namespace ld
{

struct Entity
{
  Entity()
    : type(std::string()),
      texture(std::string()),
      pos(0.f, 0.f),
      floor(0),
      dirty(false)
  {}

  std::string type;
  std::string texture;
  Eigen::Vector2f pos;
  int floor;
  bool dirty;
};

}

#endif /* ENTITY_H */
