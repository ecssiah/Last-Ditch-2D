#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>

#include "Label.h"
#include "Text.h"
#include "Scalable.h"

namespace ld
{

struct Button : public Label
{
  Button()
    : clicked(false)
  {}

  bool clicked;
};

}

#endif /* BUTTON_H */
