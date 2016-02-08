#ifndef ITEM_H
#define ITEM_H

#include "Entity.h"

namespace ld
{

struct Item : public Entity
{
  Item()
    : Entity(),
      radius(.5f)
  {}

  float radius;
};

}

#endif /* ITEM_H */
