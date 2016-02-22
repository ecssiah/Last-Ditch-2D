#ifndef INTERFACECONSTANTS_H
#define INTERFACECONSTANTS_H

#include <string>
#include <unordered_map>

namespace ld
{

struct RenderData
{
  RenderData(int _x, int _y, int _w, int _h)
    : x(_x),
      y(_y),
      w(_w),
      h(_h)
  {}
};

static std::unordered_map<std::string, RenderData>
RENDER_DATA(
{
  {"basic_backdrop", {4, 4, 32, 16}},
  {"basic_backdrop_tl", {0, 0, 3, 3}},
  {"basic_backdrop_tt", {4, 0, 32, 3}},
  {"basic_backdrop_tr", {37, 0, 3, 3}},
  {"basic_backdrop_rr", {37, 4, 3, 16}},
  {"basic_backdrop_br", {37, 21, 3, 3}},
  {"basic_backdrop_bb", {0, 0, 3, 3}},
  {"basic_backdrop_bl", {0, 4, 3, 3}},
  {"basic_backdrop_ll", {0, 21, 3, 16}},
});

}

#endif /* INTERFACECONSTANTS_H */
