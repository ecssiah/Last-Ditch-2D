#ifndef ITEM_H
#define ITEM_H

#include "Entity.h"

namespace ld
{

struct Item : public Entity
{
  Item()
    : Entity(),
      weight(1.f),
      radius(.5f),
      contained(false)
  {}

  float weight;
  float radius;
  bool contained;
};

}

#endif /* ITEM_H */
