#ifndef MAPCONSTANTS_H
#define MAPCONSTANTS_H

#include <string>
#include <unordered_map>

#include "../components/ClipData.h"
#include "RenderConstants.h"

namespace ld
{

constexpr int NUM_CHUNKS_X(2);
constexpr int NUM_CHUNKS_Y(2);
constexpr int TILES_PER_CHUNK_X(12);
constexpr int TILES_PER_CHUNK_Y(12);
constexpr int MAP_SIZE_X(NUM_CHUNKS_X * TILES_PER_CHUNK_X);
constexpr int MAP_SIZE_Y(NUM_CHUNKS_Y * TILES_PER_CHUNK_Y);
constexpr int NUM_FLOORS(2);


static std::unordered_map<std::string, std::string> MAP_TYPE_TO_TEXTURE(
{
  {"chunk1", "chunk_floor1"},
  {"wall1", "tileset1"},
  {"door1", "tileset1"},
  {"floor1", "tileset1"},
  {"stairs_up1", "tileset1"},
  {"stairs_down1", "tileset1"},
});


static std::unordered_map<std::string, ClipData> MAP_CLIP_DATA(
{
  {"wall1",
    {0 * PIXELS_PER_UNIT, 0 * PIXELS_PER_UNIT, PIXELS_PER_UNIT, PIXELS_PER_UNIT}},
  {"door1_closed",
    {0 * PIXELS_PER_UNIT, 1 * PIXELS_PER_UNIT, PIXELS_PER_UNIT, PIXELS_PER_UNIT}},
  {"door1_open",
    {1 * PIXELS_PER_UNIT, 1 * PIXELS_PER_UNIT, PIXELS_PER_UNIT, PIXELS_PER_UNIT}},
  {"stairs_down1",
    {0 * PIXELS_PER_UNIT, 2 * PIXELS_PER_UNIT, PIXELS_PER_UNIT, PIXELS_PER_UNIT}},
  {"stairs_up1",
    {1 * PIXELS_PER_UNIT, 2 * PIXELS_PER_UNIT, PIXELS_PER_UNIT, PIXELS_PER_UNIT}},
  {"floor1",
    {0 * PIXELS_PER_UNIT, 3 * PIXELS_PER_UNIT, PIXELS_PER_UNIT, PIXELS_PER_UNIT}},
});


}

#endif /* MAPCONSTANTS_H */
