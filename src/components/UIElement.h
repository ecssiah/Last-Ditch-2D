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
      pos(0, 0)
  {}

  bool clicked;
  std::string type;
  std::string texture;
  std::string text;
  std::string text_texture;
  Eigen::Vector2i pos;
};

}

#endif /* UIELEMENT_H */
