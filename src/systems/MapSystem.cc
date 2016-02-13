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
    chunks(NUM_CHUNKS_X, {NUM_CHUNKS_Y, {NUM_FLOORS, Chunk()}}),
    rooms(NUM_FLOORS)
{
  setup_map();

  cout << "Map system ready" << endl;
}


void MapSystem::update()
{
  if (dirty)
  {
    dirty = false;

    for (auto floor(0); floor < NUM_FLOORS; ++floor)
    {
      for (auto x(0); x < NUM_CHUNKS_X; ++x)
      {
	for (auto y(0); y < NUM_CHUNKS_Y; ++y)
	{
	  auto& chunk(chunks[x][y][floor]);

	  if (chunk.dirty)
	  {
	    chunk.dirty = false;

	    for (auto cx(0); cx < TILES_PER_CHUNK_X; ++cx)
	    {
	      for (auto cy(0); cy < TILES_PER_CHUNK_Y; ++cy)
	      {
		auto& entity(chunk.entities[cx][cy]);

		if (entity.dirty)
		{
		  entity.dirty = false;
		}
	      }
	    }
	  }
	}
      }
    }
  }
}


void MapSystem::setup_map()
{
  for (auto floor(0); floor < NUM_FLOORS; ++floor)
  {
    for (auto x(0); x < NUM_CHUNKS_X; ++x)
    {
      for (auto y(0); y < NUM_CHUNKS_Y; ++y)
      {
	auto& chunk(chunks[x][y][floor]);

	chunk.pos = {x * TILES_PER_CHUNK_X, y * TILES_PER_CHUNK_Y};
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
    set_entity("wall1", x, y_, floor_);
    set_entity("wall1", x, y_ + h_ - 1, floor_);
  }

  for (auto y(y_); y < y_ + h_; ++y)
  {
    set_entity("wall1", x_, y, floor_);
    set_entity("wall1", x_ + w_ - 1, y, floor_);
  }

  for (auto x(x_ + 1); x < x_ + w_ - 1; ++x)
    for (auto y(y_ + 1); y < y_ + h_ - 1; ++y)
      set_floor_entity("floor1", x, y, floor_);

  set_door("door1", x_, y_ + h_ / 2, floor_);
  set_floor_entity("floor1", x_, y_ + h_ / 2, floor_);

  set_entity("", x_, y_ + h_ / 2 - 2, floor_, 0, false);
  set_floor_entity("floor1", x_, y_ + h_ / 2 - 2, floor_);

  set_entity("stairs_up1", x_ + w_ / 2 + 1, y_ + h_ / 2 + 1, floor_, 90, false);
  set_entity("stairs_down1", x_ + w_ / 2, y_ + h_ / 2 - 1, floor_, 0, false);

  rooms[floor_].push_back({x_, y_, w_, h_, floor_});
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


Entity& MapSystem::get_entity(int x, int y, int floor)
{
  auto& chunk(chunks[x / TILES_PER_CHUNK_X][y / TILES_PER_CHUNK_Y][floor]);

  return chunk.entities[x % TILES_PER_CHUNK_X][y % TILES_PER_CHUNK_Y];
}


Entity& MapSystem::get_entity(float x, float y, int floor)
{
  int ix(std::floor(x));
  int iy(std::floor(y));

  return get_entity(ix, iy, floor);
}


void MapSystem::set_entity(
  string type, int x, int y, int floor, float rotation, bool solid)
{
  Entity entity;
  entity.type = type;
  entity.texture_name = TYPE_TO_TEXTURE[type];
  entity.pos = {x, y};
  entity.floor = floor;
  entity.solid = solid;
  entity.rotation = rotation;

  get_chunk(x, y, floor).entities[x % TILES_PER_CHUNK_X][y % TILES_PER_CHUNK_Y] = entity;
}


void MapSystem::set_door(
  string type, int x, int y, int floor, float rotation, bool solid)
{
  Door door;
  door.type = type;
  door.texture_name = TYPE_TO_TEXTURE[type];
  door.properties.door = true;
  door.pos = {x, y};
  door.floor = floor;
  door.solid = solid;
  door.rotation = rotation;
  door.locked = false;

  get_chunk(x, y, floor).entities[x % TILES_PER_CHUNK_X][y % TILES_PER_CHUNK_Y] = door;
}


void MapSystem::open_door(Door& door, bool open)
{
  if (door.locked) return;

  if (open)
  {
    door.open = true;
    door.type = "";
  }
  else
  {
    door.open = false;
    door.type = "door1";
  }

  request_cleanup(door);
}


Entity& MapSystem::get_floor_entity(int x, int y, int floor)
{
  auto& chunk(chunks[x / TILES_PER_CHUNK_X][y / TILES_PER_CHUNK_Y][floor]);

  return chunk.floor_entities[x % TILES_PER_CHUNK_X][y % TILES_PER_CHUNK_Y];
}


Entity& MapSystem::get_floor_entity(float x, float y, int floor)
{
  int ix(std::floor(x));
  int iy(std::floor(y));

  return get_floor_entity(ix, iy, floor);
}


void MapSystem::set_floor_entity(
  string type, int x, int y, int floor, float rotation, bool solid)
{
  Entity entity;
  entity.type = type;
  entity.texture_name = TYPE_TO_TEXTURE[type];
  entity.pos = {x, y};
  entity.solid = solid;
  entity.rotation = rotation;
  entity.floor = floor;

  get_chunk(x, y, floor).floor_entities[x % TILES_PER_CHUNK_X][y % TILES_PER_CHUNK_Y] = entity;
}


void MapSystem::request_cleanup(Entity& entity)
{
  int x(entity.pos.x());
  int y(entity.pos.y());

  auto& chunk(get_chunk(x, y, entity.floor));

  dirty = true;
  chunk.dirty = true;
  entity.dirty = true;
}
