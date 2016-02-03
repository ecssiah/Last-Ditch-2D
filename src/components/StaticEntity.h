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
      size(.5)
  {}

  std::string type;
  Eigen::Vector2f pos;
  double size;
};

}

#endif /* STATICENTITY_H */
