#ifndef TEXTELEMENT_H
#define TEXTELEMENT_H

#include <string>

#include "UIElement.h"

namespace ld
{

struct TextElement : public UIElement
{
  TextElement()
    : UIElement(),
      text(std::string())
  {}

  std::string text;
};

}

#endif /* TEXTELEMENT_H */
