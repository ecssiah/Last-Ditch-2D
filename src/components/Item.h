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
      radius(.5f),
      name(std::string()),
      category(WEAPONS),
      value(0.1f),
      quality(0.1f),
      weight(0.1f),
      volume(0.1f),
      contained(false)
  {}

  bool operator <(const Item& rhs) const
  {
    return name < rhs.name;
  }

  std::string name;
  float radius;
  ItemCategory category;

  float value;
  float quality;
  float weight;
  float volume;

  bool contained;
};

}

#endif /* ITEM_H */
