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
      frame(0),
      frame_time(0),
      frame_length(.25f),
      base_speed(1.f),
      direction(0, 0),
      inventory(),
      equipment(),
      body(nullptr)
  {
    clip_rect.w = PIXELS_PER_UNIT;
    clip_rect.h = PIXELS_PER_UNIT;
  }

  std::string name;
  std::string texture;
  std::string animation;

  unsigned frame;
  float frame_time;
  float frame_length;

  float base_speed;
  Eigen::Vector2f direction;

  Inventory inventory;
  Equipment equipment;

  b2Body* body;
};

}

#endif /* CHARACTER_H */
