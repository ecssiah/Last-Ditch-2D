#ifndef MAPSYSTEM_H
#define MAPSYSTEM_H

#include <array>
#include <memory>
#include <vector>

#include "../components/Chunk.h"
#include "../components/Tile.h"

using Tiles = std::vector<Tile>;

namespace ld
{

static constexpr int NUM_CHUNKS_X = 2;
static constexpr int NUM_CHUNKS_Y = 2;
static constexpr int TILES_PER_CHUNK_X = 20;
static constexpr int TILES_PER_CHUNK_Y = 20;
static constexpr int MAP_SIZE_X = NUM_CHUNKS_X * TILES_PER_CHUNK_X;
static constexpr int MAP_SIZE_Y = NUM_CHUNKS_Y * TILES_PER_CHUNK_Y;
static constexpr int NUM_FLOORS = 2;

class MapSystem
{
  void setup_map();

  void layout_room(int x, int y, int w, int h, int floor);
  void set_tile(std::string type, int x, int y, int floor, bool solid = false);

  std::vector<std::vector<Chunk>> chunks;
  std::vector<std::vector<Tiles>> tiles;

public:
  MapSystem();

  Tile& get_tile(int x, int y, int floor) { return tiles[x][y][floor]; }
};

}

#endif /* MAPSYSTEM_H */
