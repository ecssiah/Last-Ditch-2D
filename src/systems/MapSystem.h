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

  bool dirty;
  std::vector<Tile*> dirty_tiles;

  std::vector<std::vector<std::vector<Chunk>>> chunks;
  std::vector<std::vector<Room>> rooms;

public:
  MapSystem();

  void update();

  std::vector<Tile*>& get_dirty_tiles() { return dirty_tiles; }
  void request_tile_update(int x, int y, int floor);

  Chunk& get_chunk(int x, int y, int floor);
  Chunk& get_chunk(float x, float y, int floor);

  Tile& get_tile(int x, int y, int floor);
  Tile& get_tile(float x, float y, int floor);
  void set_tile(
    std::string type, int x, int y, int floor, float rotation = 0, bool solid = true);

  Tile& get_floor_tile(int x, int y, int floor);
  Tile& get_floor_tile(float x, float y, int floor);
  void set_floor_tile(
    std::string type, int x, int y, int floor, float rotation = 0, bool solid = true);
};

}

#endif /* MAPSYSTEM_H */
