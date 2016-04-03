#ifndef SCROLLABLEELEMENT_H
#define SCROLLABLEELEMENT_H

#include <unordered_map>

#include "Item.h"
#include "UIElement.h"

namespace ld
{

struct ScrollableElement : public UIElement
{
  ScrollableElement() = default;

  int offset;
};

}

#endif /* SCROLLABLEELEMENT_H */
