#include "MapSystem.h"

#include <cassert>
#include <eigen3/Eigen/Geometry>
#include <iostream>

#include "../constants/MapConstants.h"
#include "../constants/RenderConstants.h"
#include "../components/Door.h"

using namespace ld;
using namespace Eigen;
using namespace std;

MapSystem::MapSystem()
  : dirty(false),
    chunks(NUM_CHUNKS_X, {NUM_CHUNKS_Y, {NUM_FLOORS, Chunk()}})
{
  setup_map();

  cout << "Map system ready" << endl;
}


void MapSystem::update()
{
}


void MapSystem::setup_map()
{
  for (auto floor(0); floor < NUM_FLOORS; ++floor)
  {
    for (auto cx(0); cx < NUM_CHUNKS_X; ++cx)
    {
      for (auto cy(0); cy < NUM_CHUNKS_Y; ++cy)
      {
	auto& chunk(chunks[cx][cy][floor]);

	chunk.pos = {cx * TILES_PER_CHUNK_X, cy * TILES_PER_CHUNK_Y};
	chunk.type = "chunk1";
	chunk.texture_name = TYPE_TO_TEXTURE[chunk.type];
	chunk.floor = floor;
      }
    }
  }

  layout_room(5, 4, 9, 11, 0);
}


void MapSystem::layout_room(int x_, int y_, int w_, int h_, int floor_)
{
  for (auto x(x_); x < x_ + w_; ++x)
  {
    set_main_tile("wall1", x, y_, floor_);
    set_main_tile("wall1", x, y_ + h_ - 1, floor_);
  }

  for (auto y(y_); y < y_ + h_; ++y)
  {
    set_main_tile("wall1", x_, y, floor_);
    set_main_tile("wall1", x_ + w_ - 1, y, floor_);
  }

  for (auto x(x_ + 1); x < x_ + w_ - 1; ++x)
    for (auto y(y_ + 1); y < y_ + h_ - 1; ++y)
      set_floor_tile("floor1", x, y, floor_);

  create_door("door1", x_, y_, floor_);
  set_floor_tile("floor1", x_, y_, floor_, 0, false);

  create_door("door1", x_, y_ + h_ / 2, floor_);
  set_floor_tile("floor1", x_, y_ + h_ / 2, floor_, 0, false);
  set_main_tile("wall1", x_ - 1, y_ + h_ / 2, floor_);

  set_main_tile("", x_, y_ + h_ / 2 - 2, floor_, 0, false);
  set_floor_tile("floor1", x_, y_ + h_ / 2 - 2, floor_);

  set_main_tile("stairs_up1", x_ + w_ / 2 + 1, y_ + h_ / 2 + 1, floor_, 90, false);
  set_main_tile("stairs_down1", x_ + w_ / 2, y_ + h_ / 2 - 1, floor_, 0, false);
}


Chunk& MapSystem::get_chunk(int x, int y, int floor)
{
  return chunks[x / TILES_PER_CHUNK_X][y / TILES_PER_CHUNK_Y][floor];
}


Chunk& MapSystem::get_chunk(float x, float y, int floor)
{
  int ix(std::floor(x / TILES_PER_CHUNK_X));
  int iy(std::floor(y / TILES_PER_CHUNK_Y));

  return get_chunk(ix, iy, floor);
}


Tile& MapSystem::get_main_tile(int x, int y, int floor)
{
  auto& chunk(chunks[x / TILES_PER_CHUNK_X][y / TILES_PER_CHUNK_Y][floor]);

  return chunk.main_tiles[x % TILES_PER_CHUNK_X][y % TILES_PER_CHUNK_Y];
}


Tile& MapSystem::get_main_tile(float x, float y, int floor)
{
  int ix(std::floor(x));
  int iy(std::floor(y));

  return get_main_tile(ix, iy, floor);
}


void MapSystem::set_main_tile(
  string type, int x, int y, int floor, float rotation, bool solid)
{
  auto& tile(get_main_tile(x, y, floor));

  tile.type = type;
  tile.texture_name = TYPE_TO_TEXTURE[type];
  tile.pos = {x, y};
  tile.floor = floor;
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
  tile.texture_name = TYPE_TO_TEXTURE[type];
  tile.pos = {x, y};
  tile.solid = solid;
  tile.rotation = rotation;
  tile.floor = floor;
}


void MapSystem::create_door(string type, int x, int y, int floor, float rotation)
{
  set_main_tile("", x, y, floor, rotation, true);

  Door door;
  door.type = type;
  door.texture_name = TYPE_TO_TEXTURE[type];
  door.pos = {x, y};
  door.floor = floor;
  door.rotation = rotation;

  auto& chunk(get_chunk(x, y, floor));
  chunk.doors.push_back(door);
}


void MapSystem::open_door(Door& door)
{
  if (!door.locked)
  {
    door.open = !door.open;

    auto& chunk(get_chunk(door.pos.x(), door.pos.y(), door.floor));

    dirty = true;
    chunk.dirty = true;
    door.dirty = true;
  }
}
