#ifndef ITEMCONSTANTS_H
#define ITEMCONSTANTS_H

#include <string>
#include <unordered_map>
#include <vector>

#include "../components/ClipData.h"
#include "RenderConstants.h"

namespace ld
{

enum ItemCategory
{
  ALL,
  WEAPON,
  CLOTHING,
  UTILITY,
  PRODUCTION
};

struct ItemInfo
{
  ItemInfo() = default;

  ItemInfo(
    std::string _name, ItemCategory _category, std::string _texture, ClipData _clip_data
  )
    : name(_name),
      category(_category),
      texture(_texture),
      clip_data(_clip_data)
  {}

  std::string name;
  ItemCategory category;
  std::string texture;
  ClipData clip_data;
};


constexpr unsigned HALF_UNIT(PIXELS_PER_UNIT / 2);


static std::unordered_map<std::string, ItemInfo>
ITEM_INFO(
{
  {
    "scrub",
    {
      "Scrub",
      PRODUCTION,
      "items1",
      {0 * HALF_UNIT, 0 * HALF_UNIT, HALF_UNIT, HALF_UNIT}
    }
  },
  {
    "case-small",
    {
      "Case, small",
      UTILITY,
      "items1",
      {1 * HALF_UNIT, 0 * HALF_UNIT, HALF_UNIT, HALF_UNIT}
    }
  },
  {
    "scrap",
    {
      "Scrap",
      PRODUCTION,
      "items1",
      {2 * HALF_UNIT, 0 * HALF_UNIT, HALF_UNIT, HALF_UNIT}
    }
  },
});

}

#endif /* ITEMCONSTANTS_H */
