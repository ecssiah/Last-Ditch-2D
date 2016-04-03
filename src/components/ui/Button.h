#ifndef BUTTON_H
#define BUTTON_H

#include "Element.h"

namespace ld
{

struct Button : public Element
{
  Button() = default;

  bool clicked;
};

}

#endif /* BUTTON_H */
