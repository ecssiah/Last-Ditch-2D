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
  void layout_room(
    unsigned x, unsigned y, unsigned w, unsigned h, unsigned floor);
  void create_door(
    std::string type, unsigned x, unsigned y, unsigned floor, unsigned direction = 0);

  bool dirty;

  std::vector<std::vector<std::vector<Chunk>>> chunks;

public:
  MapSystem();

  void update();

  const bool& is_dirty() const { return dirty; }
  void set_dirty(bool dirty_) { dirty = dirty_; }

  void use_door(Door& door);

  Chunk& get_chunk(unsigned x, unsigned y, unsigned floor);
  Tile& get_main_tile(unsigned x, unsigned y, unsigned floor);
  Tile& get_floor_tile(unsigned x, unsigned y, unsigned floor);

  void set_main_tile(
    std::string texture_name,
    unsigned x, unsigned y, unsigned floor,
    unsigned rotation = 0, bool solid = true);
  void set_floor_tile(
    std::string texture_name,
    unsigned x, unsigned y, unsigned floor,
    unsigned rotation = 0);
};

}

#endif /* MAPSYSTEM_H */
