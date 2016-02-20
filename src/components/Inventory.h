#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>

#include "Item.h"

namespace ld
{

struct Inventory
{
  Inventory()
    : weight(0.f),
      max_weight(20.f),
      area(0.f),
      max_area(100.f),
      items()
  {}

  float weight, max_weight;
  float area, max_area;

  std::vector<Item> items;
};

}


#endif /* INVENTORY_H */
