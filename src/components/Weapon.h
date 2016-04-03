#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"

namespace ld
{

struct Weapon : public Item
{
  Weapon() = default;

  float physical_damage;
  float energy_damage;
  float burning_damage;
};

}

#endif /* WEAPON_H */
