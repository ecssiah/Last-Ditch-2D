#ifndef CHARACTER_H
#define CHARACTER_H

#include <Box2D/Box2D.h>
#include <eigen3/Eigen/Geometry>
#include <SDL2/SDL.h>
#include <string>

#include "Entity.h"
#include "Inventory.h"
#include "Equipment.h"
#include "../constants/RenderConstants.h"

namespace ld
{

struct Character : public Entity
{
  Character()
    : Entity(),
      name(std::string()),
      texture(std::string()),
      animation(std::string()),
      arm_texture(std::string()),
      arm_animation(std::string()),
      frame(0),
      arm_frame(0),
      frame_time(0.f),
      arm_frame_time(0.f),
      frame_length(.22f),
      arm_frame_length(.22f),
      radius(.5f),
      speed(1.f),
      vel(0.f, 0.f),
      inventory(),
      equipment(),
      body(nullptr),
      clip_rect(),
      arm_clip_rect()
  {
    clip_rect.w = PIXELS_PER_UNIT;
    clip_rect.h = PIXELS_PER_UNIT;
    arm_clip_rect.w = PIXELS_PER_UNIT;
    arm_clip_rect.h = PIXELS_PER_UNIT;
  }

  std::string name;
  std::string texture, animation;
  std::string arm_texture, arm_animation;

  int frame, arm_frame;

  float frame_time, arm_frame_time;
  float frame_length, arm_frame_length;

  float radius;
  float speed;
  Eigen::Vector2f vel;

  Inventory inventory;
  Equipment equipment;

  b2Body* body;
  SDL_Rect clip_rect, arm_clip_rect;
};

}

#endif /* CHARACTER_H */
