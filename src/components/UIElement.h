#ifndef UIELEMENT_H
#define UIELEMENT_H

#include <eigen3/Eigen/Geometry>
#include <SDL2/SDL.h>

namespace ld
{

struct UIElement
{
  UIElement()
    : type(std::string()),
      texture(std::string()),
      pos(0, 0),
      size(60, 20),
      clip_rect()
  {}

  std::string type;
  std::string texture;

  Eigen::Vector2i pos;
  Eigen::Vector2i size;

  SDL_Rect clip_rect;
};

}

#endif /* UIELEMENT_H */
