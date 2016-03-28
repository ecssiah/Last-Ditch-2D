#ifndef ITEM_H
#define ITEM_H

#include <functional>

#include "../constants/ItemConstants.h"
#include "Entity.h"

namespace ld
{

struct Item : public Entity
{
  Item()
    : Entity(),
      name(std::string()),
      category(WEAPON),
      weight(1.f),
      radius(.5f),
      contained(false)
  {}

  bool operator <(const Item& rhs) const
  {
    return name < rhs.name;
  }

  std::string name;
  ItemCategory category;
  float weight;
  float radius;
  bool contained;
};

}

#endif /* ITEM_H */
