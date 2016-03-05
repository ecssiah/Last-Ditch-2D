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


struct TileInfo
{
  TileInfo() = default;

  TileInfo(std::string _texture, ClipData _clip_data)
    : texture(_texture),
      clip_data(_clip_data)
  {}

  std::string texture;
  ClipData clip_data;
};


static std::unordered_map<std::string, TileInfo>
TILE_INFO(
{
  {
    "black",
    {
      "tileset1",
      {0 * PIXELS_PER_UNIT, 0 * PIXELS_PER_UNIT, PIXELS_PER_UNIT, PIXELS_PER_UNIT}
    }
  },
  {
    "wall1",
    {
      "tileset1",
      {1 * PIXELS_PER_UNIT, 0 * PIXELS_PER_UNIT, PIXELS_PER_UNIT, PIXELS_PER_UNIT}
    }
  },
  {
    "door1-open",
    {
      "tileset1",
      {0 * PIXELS_PER_UNIT, 1 * PIXELS_PER_UNIT, PIXELS_PER_UNIT, PIXELS_PER_UNIT}
    }
  },
  {
    "door1-closed",
    {
      "tileset1",
      {1 * PIXELS_PER_UNIT, 1 * PIXELS_PER_UNIT, PIXELS_PER_UNIT, PIXELS_PER_UNIT}
    }
  },
  {
    "floor1",
    {
      "tileset1",
      {0 * PIXELS_PER_UNIT, 3 * PIXELS_PER_UNIT, PIXELS_PER_UNIT, PIXELS_PER_UNIT}
    }
  },
  {
    "stairs1-up",
    {
      "tileset1",
      {1 * PIXELS_PER_UNIT, 2 * PIXELS_PER_UNIT, PIXELS_PER_UNIT, PIXELS_PER_UNIT}
    }
  },
  {
    "stairs1-down",
    {
      "tileset1",
      {0 * PIXELS_PER_UNIT, 2 * PIXELS_PER_UNIT, PIXELS_PER_UNIT, PIXELS_PER_UNIT}
    }
  },
});

}

#endif /* MAPCONSTANTS_H */
