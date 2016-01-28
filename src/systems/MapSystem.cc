#include "MapSystem.h"

#include <eigen3/Eigen/Geometry>
#include <iostream>

#include "../constants/MapConstants.h"

using namespace ld;
using namespace Eigen;
using namespace std;

MapSystem::MapSystem()
  : chunks(NUM_CHUNKS_X, {NUM_CHUNKS_Y, {NUM_FLOORS, Chunk()}}),
    rooms(NUM_FLOORS)
{
  setup_map();

  cout << "Map system ready" << endl;
}


void MapSystem::setup_map()
{
  for (auto floor = 0; floor < NUM_FLOORS; ++floor)
  {
    for (auto x = 0; x < NUM_CHUNKS_X; ++x)
    {
      for (auto y = 0; y < NUM_CHUNKS_Y; ++y)
      {
	auto& chunk = chunks[x][y][floor];

	chunk.pos = Vector2i(x * TILES_PER_CHUNK_X, y * TILES_PER_CHUNK_Y);
      }
    }
  }

  layout_room(2, 2, 4, 4, 0);
}


void MapSystem::layout_room(int x, int y, int w, int h, int floor)
{
  Room room(x, y, w, h, floor);

  for (auto x = room.x; x < room.x + room.w; ++x)
  {
    set_tile("wall1", x, room.y, floor);
    set_tile("wall1", x, room.y + room.h - 1, floor);
  }

  for (auto y = room.y; y < room.y + room.h; ++y)
  {
    set_tile("wall1", room.x, y, floor);
    set_tile("wall1", room.x + room.w - 1, y, floor);
  }

  set_tile("door1", room.x, room.y + room.h / 2, floor);

  rooms[floor].push_back(room);
}


Tile& MapSystem::get_tile(int x, int y, int floor)
{
  auto& chunk = chunks[x / TILES_PER_CHUNK_X][y / TILES_PER_CHUNK_Y][floor];

  return chunk.tiles[x % TILES_PER_CHUNK_X][y % TILES_PER_CHUNK_Y];
}


void MapSystem::set_tile(string type, int x, int y, int floor, float rotation, bool solid)
{
  auto& tile = get_tile(x, y, floor);
  tile.type = type;
  tile.pos = {x, y};
  tile.solid = solid;
  tile.rotation = rotation;
}
