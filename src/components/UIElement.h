#ifndef UIELEMENT_H
#define UIELEMENT_H

#include <eigen3/Eigen/Geometry>

namespace ld
{

struct UIElement
{
  UIElement()
    : clicked(false),
      type(std::string()),
      texture(std::string()),
      text(std::string()),
      text_texture(std::string()),
      pos(0, 0),
      size(120, 20),
      clip_rect(),
      text_clip_rect()
  {}

  bool clicked;
  std::string type;
  std::string texture;
  std::string text;
  std::string text_texture;
  Eigen::Vector2i pos;
  Eigen::Vector2i size;

  SDL_Rect clip_rect;
  SDL_Rect text_clip_rect;
};

}

#endif /* UIELEMENT_H */
