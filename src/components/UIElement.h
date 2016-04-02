#ifndef UIELEMENT_H
#define UIELEMENT_H

#include <eigen3/Eigen/Geometry>
#include <SDL2/SDL.h>

namespace ld
{

struct UIElement
{
  UIElement() = default;

  std::string type;
  std::string texture;

  SDL_Rect clip_rect;
  SDL_Rect dest_rect;
};

}

#endif /* UIELEMENT_H */
