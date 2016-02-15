#ifndef USER_H
#define USER_H

#include <Box2D/Box2D.h>
#include <eigen3/Eigen/Geometry>
#include <SDL2/SDL.h>
#include <string>

#include "Entity.h"

namespace ld
{

struct User : public Entity
{
  User()
    : Entity(),
      name(std::string()),
      radius(.5f),
      speed(100.f),
      vel(0.f, 0.f),
      clip_rect(),
      body(nullptr)
  {}

  std::string name;

  float radius;
  float speed;
  Eigen::Vector2f vel;

  SDL_Rect clip_rect;

  b2Body* body;
};

}

#endif /* USER_H */
