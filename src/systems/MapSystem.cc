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

	chunk.pos = {x * TILES_PER_CHUNK_X, y * TILES_PER_CHUNK_Y};
      }
    }
  }

  layout_room(4, 4, 6, 6, 0);
}


void MapSystem::layout_room(int x_, int y_, int w_, int h_, int floor_)
{
  for (auto x = x_; x < x_ + w_; ++x)
  {
    set_tile("wall1", x, y_, floor_);
    set_tile("wall1", x, y_ + h_ - 1, floor_);
  }

  for (auto y = y_; y < y_ + h_; ++y)
  {
    set_tile("wall1", x_, y, floor_);
    set_tile("wall1", x_ + w_ - 1, y, floor_);
  }

  set_tile("door1", x_, y_ + h_ / 2, floor_);
  set_tile("stairs1", x_ + w_ / 2, y_ + h_ / 2, floor_);

  rooms[floor_].push_back({x_, y_, w_, h_, floor_});
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
