#ifndef ELEMENT_H
#define ELEMENT_H

#include <eigen3/Eigen/Geometry>
#include <SDL2/SDL.h>

namespace ld
{

struct Element
{
  Element() = default;

  std::string type;
  std::string texture;

  SDL_Rect clip_rect;
  SDL_Rect dest_rect;
};

}

#endif /* ELEMENT_H */
