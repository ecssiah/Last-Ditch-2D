#ifndef MAPSYSTEM_H
#define MAPSYSTEM_H

#include <array>
#include <memory>
#include <vector>

#include "../constants/MapConstants.h"
#include "../components/Chunk.h"
#include "../components/Door.h"
#include "../components/Room.h"

namespace ld
{

class MapSystem
{
  void setup_map();
  void layout_room(int x, int y, int w, int h, int floor);

  void request_cleanup(Entity& door);

  bool dirty;

  std::vector<std::vector<std::vector<Chunk>>> chunks;
  std::vector<std::vector<Room>> rooms;

public:
  MapSystem();
  ~MapSystem();

  void update();

  Chunk& get_chunk(int x, int y, int floor);
  Chunk& get_chunk(float x, float y, int floor);

  Entity& get_entity(int x, int y, int floor);
  Entity& get_entity(float x, float y, int floor);
  Entity& get_floor_entity(int x, int y, int floor);
  Entity& get_floor_entity(float x, float y, int floor);

  void set_entity(
    std::string texture_name,
    int x, int y, int floor,
    float rotation = 0.f, bool solid = true);
  void set_door(
    std::string texture_name,
    int x, int y, int floor,
    float rotation = 0.f, bool solid = true);
  void set_floor_entity(
    std::string texture_name,
    int x, int y, int floor,
    float rotation = 0.f, bool solid = true);

  bool open_door(Door& door, bool open);
};

}

#endif /* MAPSYSTEM_H */
