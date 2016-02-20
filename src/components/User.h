#ifndef USER_H
#define USER_H

#include <Box2D/Box2D.h>
#include <eigen3/Eigen/Geometry>
#include <SDL2/SDL.h>
#include <string>

#include "Entity.h"
#include "Inventory.h"
#include "../constants/RenderConstants.h"

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
      frame(0),
      animation(std::string()),
      clip_rect(),
      body(nullptr),
      inventory()
  {
    clip_rect.w = PIXELS_PER_UNIT;
    clip_rect.h = PIXELS_PER_UNIT;
  }

  std::string name;

  float radius;
  float speed;
  Eigen::Vector2f vel;

  int frame;
  std::string animation;

  SDL_Rect clip_rect;

  b2Body* body;

  Inventory inventory;
};

}

#endif /* USER_H */
