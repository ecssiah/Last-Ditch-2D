#ifndef CHARACTER_H
#define CHARACTER_H

#include <Box2D/Box2D.h>
#include <eigen3/Eigen/Geometry>
#include <SDL2/SDL.h>
#include <string>

#include "Entity.h"
#include "Inventory.h"
#include "../constants/RenderConstants.h"

namespace ld
{

struct Character : public Entity
{
  Character()
    : Entity(),
      name(std::string()),
      body_texture(std::string()),
      body_animation(std::string()),
      arm_texture(std::string()),
      arm_animation(std::string()),
      frame(0),
      radius(.5f),
      speed(100.f),
      vel(0.f, 0.f),
      inventory(),
      body(nullptr),
      body_clip_rect(),
      arm_clip_rect()
  {
    body_clip_rect.w = PIXELS_PER_UNIT;
    body_clip_rect.h = PIXELS_PER_UNIT;
    arm_clip_rect.w = PIXELS_PER_UNIT;
    arm_clip_rect.h = PIXELS_PER_UNIT;
  }

  std::string name;
  std::string body_texture, body_animation;
  std::string arm_texture, arm_animation;

  int frame;

  float radius;
  float speed;
  Eigen::Vector2f vel;

  Inventory inventory;

  b2Body* body;
  SDL_Rect body_clip_rect, arm_clip_rect;
};
}

#endif /* CHARACTER_H */
