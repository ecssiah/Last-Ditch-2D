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
    : size(1.f, 1.f)
  {
    clip_rect.w = dest_rect.w = PIXELS_PER_UNIT;
    clip_rect.h = dest_rect.h = PIXELS_PER_UNIT;
  }

  std::string type;
  std::string texture;

  Eigen::Vector2f pos;
  Eigen::Vector2f size;

  int floor;
  bool dirty;

  SDL_Rect clip_rect;
  SDL_Rect dest_rect;
};

}

#endif /* ENTITY_H */
