#ifndef RENDERCONSTANTS_H
#define RENDERCONSTANTS_H

#include <map>
#include <string>

namespace ld
{

constexpr float PIXELS_PER_UNIT(48);
constexpr int SCREEN_SIZE_X(800);
constexpr int SCREEN_SIZE_Y(600);
constexpr int HALF_SCREEN_SIZE_X(SCREEN_SIZE_X / 2);
constexpr int HALF_SCREEN_SIZE_Y(SCREEN_SIZE_Y / 2);
constexpr float HALF_SCREEN_SIZE_X_WORLD(HALF_SCREEN_SIZE_X / (float)PIXELS_PER_UNIT);
constexpr float HALF_SCREEN_SIZE_Y_WORLD(HALF_SCREEN_SIZE_Y / (float)PIXELS_PER_UNIT);

static std::map<std::string, std::string> TYPE_TO_TEXTURE(
{
  {"kadijah", "kadijah"},
  {"chunk1", "chunk_floor1"},
  {"wall1", "tileset1"},
  {"door1", "tileset1"},
  {"floor1", "tileset1"},
  {"stairs_up1", "tileset1"},
  {"stairs_down1", "tileset1"},
  {"scrub1", "items1"},
  {"container1", "items1"},
});

}

#endif /* RENDERCONSTANTS_H */
