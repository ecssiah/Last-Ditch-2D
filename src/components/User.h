#ifndef USER_H
#define USER_H

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
      floor(0),
      radius(.5f),
      speed(100.f),
      vel(0.f, 0.f),
      clip_rect()
  {}

  std::string name;

  int floor;
  float radius;
  float speed;
  Eigen::Vector2f vel;

  SDL_Rect clip_rect;
};

}

#endif /* USER_H */
