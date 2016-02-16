#ifndef MAPSYSTEM_H
#define MAPSYSTEM_H

#include <array>
#include <memory>
#include <vector>

#include "../constants/MapConstants.h"
#include "../components/Chunk.h"
#include "../components/Door.h"
#include "../components/Tile.h"

namespace ld
{

class MapSystem
{
  void setup_map();
  void layout_room(int x, int y, int w, int h, int floor);

  void create_door(std::string type, int x, int y, int floor, float roation = 0.f);
  void open_door(Door& door);

  bool dirty;

  std::vector<std::vector<std::vector<Chunk>>> chunks;

public:
  MapSystem();

  void update();

  Chunk& get_chunk(int x, int y, int floor);
  Chunk& get_chunk(float x, float y, int floor);

  Tile& get_main_tile(int x, int y, int floor);
  Tile& get_main_tile(float x, float y, int floor);
  Tile& get_floor_tile(int x, int y, int floor);
  Tile& get_floor_tile(float x, float y, int floor);

  void set_main_tile(
    std::string texture_name,
    int x, int y, int floor,
    float rotation = 0.f, bool solid = true);
  void set_floor_tile(
    std::string texture_name,
    int x, int y, int floor,
    float rotation = 0.f, bool solid = true);
};

}

#endif /* MAPSYSTEM_H */
