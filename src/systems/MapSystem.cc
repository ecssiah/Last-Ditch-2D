#include "MapSystem.h"

#include <eigen3/Eigen/Geometry>
#include <iostream>

#include "../constants/MapConstants.h"
#include "../components/Door.h"

using namespace ld;
using namespace Eigen;
using namespace std;

MapSystem::MapSystem()
  : update(false),
    chunks(NUM_CHUNKS_X, {NUM_CHUNKS_Y, {NUM_FLOORS, Chunk()}}),
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

  layout_room(4, 4, 9, 11, 0);
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

  for (auto x = x_ + 1; x < x_ + w_ - 1; ++x)
    for (auto y = y_ + 1; y < y_ + h_ - 1; ++y)
      set_floor_tile("floor1", x, y, floor_, 0, false);

  float x = x_;
  float y = y_ + h_ / 2.f;

  get_chunk(x, y, floor_).doors.push_back({x, y});
  set_tile("door1", x_, y_ + h_ / 2, floor_, 0);

  set_floor_tile("floor1", x_, y_ + h_ / 2, floor_, 0);
  set_tile("stairs_up1", x_ + w_ / 2 + 1, y_ + h_ / 2 + 1, floor_, 90, false);
  set_tile("stairs_down1", x_ + w_ / 2, y_ + h_ / 2 - 1, floor_, 0, false);

  rooms[floor_].push_back({x_, y_, w_, h_, floor_});
}


Chunk& MapSystem::get_chunk(float x, float y, int floor)
{
  int ix(std::floor(x / TILES_PER_CHUNK_X));
  int iy(std::floor(y / TILES_PER_CHUNK_Y));

  return get_chunk(ix, iy, floor);
}


Tile& MapSystem::get_tile(int x, int y, int floor)
{
  auto& chunk(chunks[x / TILES_PER_CHUNK_X][y / TILES_PER_CHUNK_Y][floor]);

  return chunk.tiles[x % TILES_PER_CHUNK_X][y % TILES_PER_CHUNK_Y];
}


Tile& MapSystem::get_tile(float x, float y, int floor)
{
  int ix(std::floor(x));
  int iy(std::floor(y));

  return get_tile(ix, iy, floor);
}


void MapSystem::set_tile(string type, int x, int y, int floor, float rotation, bool solid)
{
  auto& tile(get_tile(x, y, floor));
  tile.type = type;
  tile.pos = {x, y};
  tile.solid = solid;
  tile.rotation = rotation;
}


Tile& MapSystem::get_floor_tile(int x, int y, int floor)
{
  auto& chunk(chunks[x / TILES_PER_CHUNK_X][y / TILES_PER_CHUNK_Y][floor]);

  return chunk.floor_tiles[x % TILES_PER_CHUNK_X][y % TILES_PER_CHUNK_Y];
}


Tile& MapSystem::get_floor_tile(float x, float y, int floor)
{
  int ix(std::floor(x));
  int iy(std::floor(y));

  return get_floor_tile(ix, iy, floor);
}


void MapSystem::set_floor_tile(
  string type, int x, int y, int floor, float rotation, bool solid)
{
  auto& tile(get_floor_tile(x, y, floor));
  tile.type = type;
  tile.pos = {x, y};
  tile.solid = solid;
  tile.rotation = rotation;
}
