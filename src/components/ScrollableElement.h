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
      scrolled_offset(0.f),
      list_elements()
  {}

  unsigned current_index;
  float scrolled_offset;
  std::vector<ListElement> list_elements;
};

}

#endif /* SCROLLABLEELEMENT_H */
