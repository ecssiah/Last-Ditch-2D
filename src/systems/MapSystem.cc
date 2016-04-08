#include "MapSystem.h"

#include <cassert>
#include <eigen3/Eigen/Geometry>
#include <iostream>

#include "../constants/MapConstants.h"
#include "../constants/RenderConstants.h"
#include "../components/Door.h"

using namespace Eigen;
using namespace std;

namespace ld
{

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

	chunk.floor = floor;
	chunk.type = "chunk1";
	chunk.texture = "chunk_floor1";

	chunk.pos = {cx * TILES_PER_CHUNK_X, cy * TILES_PER_CHUNK_Y};

	chunk.clip_rect.x = 0;
	chunk.clip_rect.y = 0;
	chunk.clip_rect.w = TILES_PER_CHUNK_X * PIXELS_PER_UNIT;
	chunk.clip_rect.h = TILES_PER_CHUNK_Y * PIXELS_PER_UNIT;

	chunk.dest_rect.x = PIXELS_PER_UNIT * chunk.pos.x();
	chunk.dest_rect.y = PIXELS_PER_UNIT * chunk.pos.y();

	printf("%f %f\n", chunk.pos.x(), chunk.pos.y());
      }
    }
  }

  layout_room(5, 4, 9, 11, 0);
}


void MapSystem::layout_room(
  unsigned _x, unsigned _y, unsigned _w, unsigned _h, unsigned _floor)
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


Chunk& MapSystem::get_chunk(unsigned cx, unsigned cy, unsigned floor)
{
  return chunks[cx][cy][floor];
}


Tile& MapSystem::get_main_tile(unsigned tx, unsigned ty, unsigned floor)
{
  unsigned cx(tx / TILES_PER_CHUNK_X);
  unsigned cy(ty / TILES_PER_CHUNK_Y);

  auto& chunk(get_chunk(cx, cy, floor));

  return chunk.main_tiles[tx % TILES_PER_CHUNK_X][ty % TILES_PER_CHUNK_Y];
}


void MapSystem::set_main_tile(
  string type, unsigned x, unsigned y, unsigned floor, unsigned direction, bool solid)
{
  auto& tile(get_main_tile(x, y, floor));

  tile.type = type;
  tile.texture = Tile_Data[type].texture;
  tile.floor = floor;
  tile.solid = solid;
  tile.direction = direction;
  tile.pos = {x, y};
  tile.clip_rect = Tile_Data[type].clip_rect;
  tile.dest_rect.x = PIXELS_PER_UNIT * tile.pos.x();
  tile.dest_rect.y = PIXELS_PER_UNIT * tile.pos.y();
}


Tile& MapSystem::get_floor_tile(unsigned tx, unsigned ty, unsigned floor)
{
  unsigned cx(tx / TILES_PER_CHUNK_X);
  unsigned cy(ty / TILES_PER_CHUNK_Y);

  auto& chunk(get_chunk(cx, cy, floor));

  return chunk.floor_tiles[tx % TILES_PER_CHUNK_X][ty % TILES_PER_CHUNK_Y];
}


void MapSystem::set_floor_tile(
  string type, unsigned x, unsigned y, unsigned floor, unsigned direction)
{
  auto& tile(get_floor_tile(x, y, floor));

  tile.type = type;
  tile.texture = Tile_Data[type].texture;
  tile.pos = {x, y};
  tile.direction = direction;
  tile.floor = floor;

  tile.clip_rect = Tile_Data[type].clip_rect;
  tile.dest_rect.x = PIXELS_PER_UNIT * tile.pos.x();
  tile.dest_rect.y = PIXELS_PER_UNIT * tile.pos.y();
  tile.dest_rect.w = PIXELS_PER_UNIT;
  tile.dest_rect.h = PIXELS_PER_UNIT;
}


void MapSystem::create_door(
  string type, unsigned x, unsigned y, unsigned floor, unsigned direction)
{
  Door door;
  door.type = type;
  door.texture = Tile_Data[type + "-closed"].texture;
  door.pos = {x, y};
  door.floor = floor;
  door.direction = direction;
  door.dest_rect.x = PIXELS_PER_UNIT * door.pos.x();
  door.dest_rect.y = PIXELS_PER_UNIT * door.pos.y();

  auto& chunk(get_chunk(x / TILES_PER_CHUNK_X, y / TILES_PER_CHUNK_Y, floor));

  chunk.doors.push_back(door);
}


void MapSystem::use_door(Door& door)
{
  if (!door.locked)
  {
    door.open = !door.open;

    auto& chunk(
      get_chunk(
	door.pos.x() / TILES_PER_CHUNK_X,
	door.pos.y() / TILES_PER_CHUNK_Y,
	door.floor));

    door.solid = !door.open;
  }
}

}
