#ifndef RENDERCONSTANTS_H
#define RENDERCONSTANTS_H

#include <map>
#include <string>

namespace ld
{

constexpr float PIXELS_PER_UNIT = 48;
constexpr int SCREEN_SIZE_X = 800;
constexpr int SCREEN_SIZE_Y = 600;

static std::map<std::string, std::string> TYPE_TO_TEXTURE =
{
  {"kadijah", "kadijah"},
  {"chunk1", "chunk_floor1"},
  {"wall1", "tileset1"},
  {"door1", "tileset1"},
  {"floor1", "tileset1"},
  {"stairs_up", "tileset1"},
  {"stairs_down", "tileset1"},
  {"scrub1", "items1"},
  {"container1", "items1"},
};

}

#endif /* RENDERCONSTANTS_H */
