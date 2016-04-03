#ifndef TEXTELEMENT_H
#define TEXTELEMENT_H

#include <string>

#include "UIElement.h"

namespace ld
{

struct TextElement : public UIElement
{
  TextElement()
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

#endif /* TEXTELEMENT_H */
