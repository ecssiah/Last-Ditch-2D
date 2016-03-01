#ifndef SCROLLABLEELEMENT_H
#define SCROLLABLEELEMENT_H

#include <vector>

#include "Item.h"
#include "UIElement.h"

namespace ld
{

struct ScrollableElement : public UIElement
{
  ScrollableElement()
    : UIElement(),
      current_index(0),
      item_list()
  {}

  unsigned current_index;
  std::vector<Item> item_list;
};

}

#endif /* SCROLLABLEELEMENT_H */
