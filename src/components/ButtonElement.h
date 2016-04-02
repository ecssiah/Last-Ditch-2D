#ifndef BUTTONELEMENT_H
#define BUTTONELEMENT_H

#include "TextElement.h"
#include "UIElement.h"

namespace ld
{

struct ButtonElement : public UIElement
{
  ButtonElement()
    : UIElement(),
      clicked(false),
      text_element()
  {}

  bool clicked;
  TextElement text_element;
};

}

#endif /* BUTTONELEMENT_H */
