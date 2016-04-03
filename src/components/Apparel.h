#ifndef APPAREL_H
#define APPAREL_H

#include "Item.h"

namespace ld
{

struct Apparel : public Item
{
  Apparel() = default;

  float physical_defense;
  float energy_defense;
  float heat_defense;
  float cold_defense;
};

}

#endif /* APPAREL_H */
