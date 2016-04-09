#ifndef LABEL_H
#define LABEL_H

#include <SDL2/SDL.h>

#include "Scalable.h"

namespace ld
{

struct Label : public Scalable
{
  Label()
    : Scalable(),
      text(std::string()),
      font("jura-small"),
      color()
  {
    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;
  }

  std::string text;
  std::string font;

  SDL_Color color;
};

}

#endif /* LABEL_H */
