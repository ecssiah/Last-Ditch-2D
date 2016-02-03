#ifndef DYNAMICENTITY_H
#define DYNAMICENTITY_H

#include <Box2D/Box2D.h>
#include <eigen3/Eigen/Geometry>
#include <SDL2/SDL.h>
#include <string>

namespace ld
{

struct DynamicEntity
{
  DynamicEntity()
    : name(std::string()),
      type(std::string()),
      pos(0, 0),
      vel(0, 0),
      speed(100),
      floor(0),
      size(.5),
      clip_rect(),
      body(nullptr)
  {}

  std::string name, type;
  Eigen::Vector2f pos, vel;
  double speed;
  int floor;
  double size;
  SDL_Rect clip_rect;
  b2Body* body;
};

}

#endif /* DYNAMICENTITY_H */
