#ifndef APPARELINFO_H
#define APPARELINFO_H

#include "ItemInfo.h"

namespace ld
{

struct ApparelInfo : public ItemInfo
{
  ApparelInfo() = default;

  float physical_defense;
  float energy_defense;
  float heat_defense;
  float cold_defense;
};

}

#endif /* APPARELINFO_H */
