#ifndef MAPSYSTEM_H
#define MAPSYSTEM_H

#include <array>
#include <memory>
#include <vector>

#include "../constants/MapConstants.h"
#include "../components/Chunk.h"
#include "../components/Room.h"
#include "../components/Tile.h"

namespace ld
{

class MapSystem
{
  void setup_map();

  void layout_room(int x, int y, int w, int h, int floor);

  std::vector<std::vector<std::vector<Chunk>>> chunks;
  std::vector<std::vector<Room>> rooms;

public:
  MapSystem();

  Chunk& get_chunk(int x, int y, int floor) { return chunks[x][y][floor]; }

  Tile& get_tile(int x, int y, int floor);
  void set_tile(
    std::string type, int x, int y, int floor, float rotation = 0, bool solid = true);
};

}

#endif /* MAPSYSTEM_H */
