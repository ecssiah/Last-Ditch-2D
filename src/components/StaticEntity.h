#ifndef STATICENTITY_H
#define STATICENTITY_H

#include <eigen3/Eigen/Geometry>
#include <string>

namespace ld
{

struct StaticEntity
{
  StaticEntity()
    : type(std::string()),
      pos(0, 0),
      radius(.25f)
  {}

  std::string type;
  Eigen::Vector2f pos;
  float radius;
};

}

#endif /* STATICENTITY_H */
