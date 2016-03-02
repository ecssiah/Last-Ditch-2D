#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>

#include "Item.h"

namespace ld
{

struct Inventory
{
  Inventory()
    : modified(false),
      weight(0.f),
      max_weight(20.f),
      area(0.f),
      max_area(100.f),
      items()
  {}

  bool modified;

  float weight, max_weight;
  float area, max_area;

  std::vector<Item> items;
};

}


#endif /* INVENTORY_H */
