#ifndef BUTTONELEMENT_H
#define BUTTONELEMENT_H

#include "TextElement.h"

namespace ld
{

struct ButtonElement : public TextElement
{
  ButtonElement() = default;

  bool clicked;
};

}

#endif /* BUTTONELEMENT_H */
