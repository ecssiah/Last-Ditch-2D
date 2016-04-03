#ifndef WEAPONINFO_H
#define WEAPONINFO_H

#include "ItemInfo.h"

namespace ld
{

struct WeaponInfo : public ItemInfo
{
  WeaponInfo() = default;

  float physical_damage;
  float energy_damage;
  float heat_damage;
  float cold_damage;
};

}

#endif /* WEAPONINFO_H */
