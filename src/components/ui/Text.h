#ifndef TEXT_H
#define TEXT_H

#include <string>

#include "Element.h"

namespace ld
{

struct Text : public Element
{
  Text()
    : font("jura-small")
  {
    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;
  }

  std::string text;
  std::string text_texture;
  std::string font;

  SDL_Color color;
  SDL_Rect text_clip_rect;
  SDL_Rect text_dest_rect;
};

}

#endif /* TEXT_H */
