#ifndef SCROLLABLEELEMENT_H
#define SCROLLABLEELEMENT_H

#include <unordered_map>

#include "ListElement.h"
#include "UIElement.h"

namespace ld
{

struct ScrollableElement : public UIElement
{
  ScrollableElement()
    : UIElement(),
      current_index(0),
      list_elements()
  {}

  unsigned current_index;
  std::vector<ListElement> list_elements;
};

}

#endif /* SCROLLABLEELEMENT_H */
