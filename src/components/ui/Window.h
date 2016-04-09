#ifndef WINDOW_H
#define WINDOW_H

#include "Scalable.h"

namespace ld
{

struct Window : public Scalable
{
  Window()
    : Scalable(),
      title(std::string()),
      font("jura-small"),
      color()
  {
    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;
  }

  std::string title;
  std::string font;

  SDL_Color color;
};

}

#endif /* WINDOW_H */
