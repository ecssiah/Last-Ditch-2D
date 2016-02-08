#ifndef STATICENTITY_H
#define STATICENTITY_H

#include <Box2D/Box2D.h>
#include <eigen3/Eigen/Geometry>
#include <string>

namespace ld
{

struct StaticEntity
{
  StaticEntity()
    : type(std::string()),
      pos(0, 0),
      radius(.25f),
      body(nullptr),
      dirty(false)
  {}

  std::string type;
  Eigen::Vector2f pos;
  float radius;
  b2Body* body;
  bool dirty;
};

}

#endif /* STATICENTITY_H */
