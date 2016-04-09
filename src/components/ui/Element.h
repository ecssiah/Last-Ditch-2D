#ifndef ELEMENT_H
#define ELEMENT_H

#include <eigen3/Eigen/Geometry>
#include <SDL2/SDL.h>
#include <string>

namespace ld
{

struct Element
{
  Element()
    : type(std::string()),
      source_texture(std::string()),
      batch_texture(std::string()),
      size(100, 20),
      clip_rect(),
      dest_rect()
  {}

  std::string type;
  std::string source_texture;
  std::string batch_texture;

  Eigen::Vector2i size;

  SDL_Rect clip_rect;
  SDL_Rect dest_rect;
};

}

#endif /* ELEMENT_H */
