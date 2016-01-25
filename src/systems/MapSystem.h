#ifndef MAPSYSTEM_H
#define MAPSYSTEM_H

#include <array>
#include <memory>
#include <vector>

#include "../constants/MapConstants.h"
#include "../components/Chunk.h"
#include "../components/Tile.h"

namespace ld
{

class MapSystem
{
  void setup_map();

  void layout_room(int x, int y, int w, int h, int floor);

  std::vector<std::vector<std::vector<Chunk>>> chunks;

public:
  MapSystem();

  Chunk& get_chunk(int x, int y, int floor) { return chunks[x][y][floor]; }
};

}

#endif /* MAPSYSTEM_H */
