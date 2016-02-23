#ifndef INTERFACECONSTANTS_H
#define INTERFACECONSTANTS_H

#include <string>
#include <unordered_map>

#include "../components/ClipData.h"

namespace ld
{

static std::unordered_map<std::string, std::string>
INTERFACE_TYPE_TO_TEXTURE(
  {"backdrop1", "interface1"},
);


static std::unordered_map<std::string, ClipData>
INTERFACE_CLIP_DATA(
{
  {"backdrop1", {4, 4, 32, 16}},
  {"backdrop1_tl", {0, 0, 3, 3}},
  {"backdrop1_tt", {4, 0, 32, 3}},
  {"backdrop1_tr", {37, 0, 3, 3}},
  {"backdrop1_rr", {37, 4, 3, 16}},
  {"backdrop1_br", {37, 21, 3, 3}},
  {"backdrop1_bb", {0, 0, 3, 3}},
  {"backdrop1_bl", {0, 4, 3, 3}},
  {"backdrop1_ll", {0, 21, 3, 16}},
});

}

#endif /* INTERFACECONSTANTS_H */
