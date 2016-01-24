#include "MapSystem.h"

#include <iostream>

using namespace ld;
using namespace std;

MapSystem::MapSystem()
  : chunks(NUM_CHUNKS_X, {NUM_CHUNKS_Y, {NUM_FLOORS, Chunk()}}),
    tiles(MAP_SIZE_X, {MAP_SIZE_Y, Tiles(NUM_FLOORS)})
{
  setup_map();

  cout << "Map system ready" << endl;
}


void MapSystem::setup_map()
{
  layout_room(2, 2, 4, 4, 0);
}


void MapSystem::layout_room(int x_, int y_, int w_, int h_, int floor)
{
  for (auto x = x_; x < x_ + w_; ++x)
  {
    set_tile("wall1", x, y_, 0);
    set_tile("wall1", x, y_ + h_ - 1, 0);
  }

  for (auto y = y_; y < y_ + h_; ++y)
  {
    set_tile("wall1", x_, y, 0);
    set_tile("wall1", x_ + w_ - 1, y, 0);
  }

  set_tile("door1", x_, y_ + h_ / 2, 0);
}

void MapSystem::set_tile(std::string type, int x, int y, int floor, bool solid)
{
  Tile& tile = tiles[x][y][floor];

  tile.type = type;
  tile.solid = solid;
}
