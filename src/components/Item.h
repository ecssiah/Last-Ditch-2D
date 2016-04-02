#ifndef ITEM_H
#define ITEM_H

#include <functional>

#include "Entity.h"

namespace ld
{

struct Item : public Entity
{
  Item()
    : Entity(),
      name(std::string()),
      category(std::string()),
      value(0.1f),
      quality(0.1f),
      weight(0.1f),
      volume(0.1f),
      radius(.5f),
      contained(false)
  {}

  bool operator <(const Item& rhs) const
  {
    return name < rhs.name;
  }

  std::string name;
  std::string category;

  float value;
  float quality;
  float weight;
  float volume;
  float radius;

  bool contained;
};

}

#endif /* ITEM_H */
