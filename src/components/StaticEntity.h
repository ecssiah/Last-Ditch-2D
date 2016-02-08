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
    : texture_name(std::string()),
      pos(0, 0),
      radius(.25f),
      rotation(0.f),
      solid(false),
      body(nullptr),
      dirty(false)
  {}

  std::string texture_name;
  Eigen::Vector2f pos;
  float radius;
  float rotation;
  bool solid;
  b2Body* body;
  bool dirty;
};

}

#endif /* STATICENTITY_H */
