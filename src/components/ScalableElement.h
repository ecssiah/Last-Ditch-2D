#ifndef SCALABLEELEMENT_H
#define SCALABLEELEMENT_H

#include <vector>

#include "UIElement.h"

namespace ld
{

struct ScalableElement : public UIElement
{
  ScalableElement()
    : UIElement(),
      border(3),
      sub_elements()
  {}

  int border;

  std::vector<UIElement> sub_elements;
};

}

#endif /* SCALABLEELEMENT_H */
