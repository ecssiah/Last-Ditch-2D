#ifndef TEXTELEMENT_H
#define TEXTELEMENT_H

#include <string>

#include "UIElement.h"

namespace ld
{

struct TextElement : public UIElement
{
  TextElement() = default;

  std::string text;
  std::string text_texture;

  SDL_Color text_color;

  SDL_Rect text_clip_rect;
  SDL_Rect text_dest_rect;
};

}

#endif /* TEXTELEMENT_H */
