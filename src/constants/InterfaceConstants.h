#ifndef INTERFACECONSTANTS_H
#define INTERFACECONSTANTS_H

#include <string>
#include <unordered_map>

#include "../components/ClipData.h"

namespace ld
{

constexpr unsigned MAIN_MENU_BUTTON_SIZE_X(200);
constexpr unsigned MAIN_MENU_BUTTON_SIZE_Y(20);

static std::unordered_map<std::string, std::string>
INTERFACE_TYPE_TO_TEXTURE(
{
  {"backdrop1", "interface1"},
});


static std::unordered_map<std::string, std::unordered_map<std::string, ClipData>>
INTERFACE_CLIP_DATA(
{
  {"backdrop1",
    {
      {"ct", {4, 4, 32, 16}},
      {"tl", {0, 0, 3, 3}},
      {"tt", {4, 0, 32, 3}},
      {"tr", {37, 0, 3, 3}},
      {"rr", {37, 4, 3, 16}},
      {"br", {37, 21, 3, 3}},
      {"bb", {0, 0, 3, 3}},
      {"bl", {0, 4, 3, 3}},
      {"ll", {0, 21, 3, 16}},
    }
  },
});

}

#endif /* INTERFACECONSTANTS_H */
