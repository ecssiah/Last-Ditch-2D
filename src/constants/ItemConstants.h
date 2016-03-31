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
  WEAPONS,
  CLOTHING,
  UTILITY,
  PRODUCTION
};

struct ItemInfo
{
  ItemInfo() = default;

  ItemInfo(
    std::string _name,
    std::string _texture,
    ItemCategory _category,
    float _value,
    float _quality,
    float _weight,
    float _volume,
    ClipData _clip_data
  )
    : name(_name),
      texture(_texture),
      category(_category),
      value(_value),
      quality(_quality),
      weight(_weight),
      volume(_volume),
      clip_data(_clip_data)
  {}

  std::string name;
  ItemCategory category;
  std::string texture;

  float value;
  float quality;
  float weight;
  float volume;

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
      "items1",
      PRODUCTION,
      .02f, .1f, 1.6f, 2.4f,
      {0 * HALF_UNIT, 0 * HALF_UNIT, HALF_UNIT, HALF_UNIT}
    }
  },
  {
    "scrap",
    {
      "Scrap",
      "items1",
      PRODUCTION,
      .02f, .1f, 2.7f, 2.4f,
      {1 * HALF_UNIT, 0 * HALF_UNIT, HALF_UNIT, HALF_UNIT}
    }
  },
  {
    "case-small",
    {
      "Case, small",
      "items1",
      UTILITY,
      .8f, .1f, .6f, .4f,
      {0 * HALF_UNIT, 1 * HALF_UNIT, HALF_UNIT, HALF_UNIT}
    }
  },
});

}

#endif /* ITEMCONSTANTS_H */
