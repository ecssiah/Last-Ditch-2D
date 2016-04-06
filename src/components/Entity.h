#ifndef ENTITY_H
#define ENTITY_H

#include <eigen3/Eigen/Geometry>
#include <SDL2/SDL.h>
#include <string>

#include "../constants/RenderConstants.h"

namespace ld
{

struct Entity
{
  Entity()
    : type(std::string()),
      texture(std::string()),
      floor(0),
      pos(0, 0),
      size(0, 0),
      clip_rect(),
      dest_rect()
  {
    dest_rect.w = PIXELS_PER_UNIT;
    dest_rect.h = PIXELS_PER_UNIT;
    clip_rect.w = PIXELS_PER_UNIT;
    clip_rect.h = PIXELS_PER_UNIT;
  }

  bool operator <(const Entity& rhs) const
  {
    return type < rhs.type;
  }

  std::string type;
  std::string texture;

  int floor;

  Eigen::Vector2f pos;
  Eigen::Vector2f size;

  SDL_Rect clip_rect;
  SDL_Rect dest_rect;
};

}

#endif /* ENTITY_H */
