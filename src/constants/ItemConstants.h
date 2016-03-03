#ifndef ITEMCONSTANTS_H
#define ITEMCONSTANTS_H

#include <string>
#include <unordered_map>
#include <vector>

#include "../components/ClipData.h"
#include "RenderConstants.h"

namespace ld
{

const std::string i1("scrub1");
const std::string i2("container1");

static std::vector<std::string> ITEM_TYPES({i1, i2});


static std::unordered_map<std::string, std::string> ITEM_DEFAULT_NAMES(
{
  {i1, "Scrub, center"},
  {i2, "Small container, empty"}
});


static std::unordered_map<std::string, std::string> ITEM_TYPE_TO_TEXTURE(
{
  {i1, "items1"},
  {i2, "items1"},
});


static std::unordered_map<std::string, ClipData> ITEM_CLIP_DATA(
{
  {i1,
    {0 * PIXELS_PER_UNIT / 2, 0 * PIXELS_PER_UNIT / 2,
     PIXELS_PER_UNIT / 2, PIXELS_PER_UNIT / 2}},
  {i2,
    {1 * PIXELS_PER_UNIT / 2, 0 * PIXELS_PER_UNIT / 2,
     PIXELS_PER_UNIT / 2, PIXELS_PER_UNIT / 2}},
});


enum Utility
{
  NONE = (1u << 0),
  FOOD = (1u << 1),
  DRINK = (1u << 2),
  WEAPON = (1u << 3),
  CLOTHING = (1u << 4),
  MEDICAL = (1u << 5),
  PRODUCTION = (1u << 6),
};


}

#endif /* ITEMCONSTANTS_H */
