#ifndef SCROLLABLEELEMENT_H
#define SCROLLABLEELEMENT_H

#include <unordered_map>

#include "Item.h"
#include "UIElement.h"

namespace ld
{

struct ScrollableElement : public UIElement
{
  ScrollableElement()
    : UIElement(),
      texture(std::string()),
      scrolled_offset(0),
      current_index(0),
      list_items()
  {}

  std::string texture;

  int scrolled_offset;
  unsigned current_index;

  std::vector<Item*> list_items;
};

}

#endif /* SCROLLABLEELEMENT_H */
