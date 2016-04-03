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

  printf("MapSystem ready\n");
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
	chunk.texture = "chunk_floor1";
	chunk.floor = floor;
      }
    }
  }

  layout_room(5, 4, 9, 11, 0);
}


void MapSystem::layout_room(int _x, int _y, int _w, int _h, int _floor)
{
  for (auto x(_x); x < _x + _w; ++x)
  {
    set_main_tile("wall1", x, _y, _floor);
    set_main_tile("wall1", x, _y + _h - 1, _floor);
  }

  for (auto y(_y); y < _y + _h; ++y)
  {
    set_main_tile("wall1", _x, y, _floor);
    set_main_tile("wall1", _x + _w - 1, y, _floor);
  }

  for (auto x(_x + 1); x < _x + _w - 1; ++x)
    for (auto y(_y + 1); y < _y + _h - 1; ++y)
      set_floor_tile("floor1", x, y, _floor);

  create_door("door1", _x, _y + _h / 2, _floor);
  set_main_tile("", _x, _y + _h / 2, _floor, 0, false);
  set_floor_tile("floor1", _x, _y + _h / 2, _floor);

  set_main_tile("stairs1-up", _x + _w / 2 + 1, _y + _h / 2 + 1, _floor);
  set_main_tile("stairs1-down", _x + _w / 2, _y + _h / 2 + 1, _floor);
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
  tile.texture = Tile_Data[type].texture;
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
  string type, int x, int y, int floor, float rotation)
{
  auto& tile(get_floor_tile(x, y, floor));

  tile.type = type;
  tile.texture = Tile_Data[type].texture;
  tile.pos = {x, y};
  tile.rotation = rotation;
  tile.floor = floor;
}


void MapSystem::create_door(string type, int x, int y, int floor, float rotation)
{
  Door door;
  door.type = type;
  door.texture = Tile_Data[type + "-closed"].texture;
  door.pos = {x, y};
  door.floor = floor;
  door.rotation = rotation;

  auto& chunk(get_chunk(x, y, floor));
  chunk.doors.push_back(door);
}


void MapSystem::use_door(Door& door)
{
  if (!door.locked)
  {
    door.open = !door.open;

    auto& chunk(get_chunk(door.pos.x(), door.pos.y(), door.floor));

    dirty = true;
    chunk.dirty = true;
    door.dirty = true;
    door.solid = !door.open;
  }
}
