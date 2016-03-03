#ifndef ITEM_H
#define ITEM_H

#include "../constants/ItemConstants.h"
#include "Entity.h"

namespace ld
{

struct Item : public Entity
{
  Item()
    : Entity(),
      name(std::string()),
      weight(1.f),
      radius(.5f),
      contained(false)
  {}

  std::string name;
  float weight;
  float radius;
  bool contained;
};

}

#endif /* ITEM_H */
