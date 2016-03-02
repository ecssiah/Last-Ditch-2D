#ifndef ITEMCONSTANTS_H
#define ITEMCONSTANTS_H

#include <string>
#include <vector>

#include "../components/ClipData.h"
#include "RenderConstants.h"

namespace ld
{

static std::vector<std::string> ITEM_TYPES(
{
  "scrub1",
  "container1",
});

static std::unordered_map<std::string, std::string> ITEM_TYPE_TO_TEXTURE(
{
  {"scrub1", "items1"},
  {"container1", "items1"},
});


static std::unordered_map<std::string, ClipData> ITEM_CLIP_DATA(
{
  {"scrub1",
    {0 * PIXELS_PER_UNIT / 2, 0 * PIXELS_PER_UNIT / 2,
     PIXELS_PER_UNIT / 2, PIXELS_PER_UNIT / 2}},
  {"container1",
    {1 * PIXELS_PER_UNIT / 2, 0 * PIXELS_PER_UNIT / 2,
     PIXELS_PER_UNIT / 2, PIXELS_PER_UNIT / 2}},
});

}

#endif /* ITEMCONSTANTS_H */
