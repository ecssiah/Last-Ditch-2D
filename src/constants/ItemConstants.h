#ifndef ITEMCONSTANTS_H
#define ITEMCONSTANTS_H

#include <string>
#include <unordered_map>
#include <vector>

#include "../components/ClipData.h"
#include "RenderConstants.h"

namespace ld
{

struct ItemInfo
{
  ItemInfo() = default;

  ItemInfo(std::string _name, std::string _texture, ClipData _clip_data)
    : name(_name),
      texture(_texture),
      clip_data(_clip_data)
  {}

  std::string name;
  std::string texture;
  ClipData clip_data;
};


static std::unordered_map<std::string, ItemInfo>
ITEM_INFO(
{
  {"scrub1",
    {
      "Scrub 1",
      "items1",
      {0 * PIXELS_PER_UNIT / 2, 0 * PIXELS_PER_UNIT / 2,
       PIXELS_PER_UNIT / 2, PIXELS_PER_UNIT / 2}
    }
  },
  {"container1",
    {
      "Container 1",
      "items1",
      {1 * PIXELS_PER_UNIT / 2, 0 * PIXELS_PER_UNIT / 2,
       PIXELS_PER_UNIT / 2, PIXELS_PER_UNIT / 2}
    }
  },
});

}

#endif /* ITEMCONSTANTS_H */
