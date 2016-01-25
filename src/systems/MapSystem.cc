#include "MapSystem.h"

#include <eigen3/Eigen/Geometry>
#include <iostream>

#include "../constants/MapConstants.h"

using namespace ld;
using namespace Eigen;
using namespace std;

MapSystem::MapSystem()
  : chunks(NUM_CHUNKS_X, {NUM_CHUNKS_Y, {NUM_FLOORS, Chunk()}})
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
}


void MapSystem::layout_room(int x_, int y_, int w_, int h_, int floor)
{
  for (auto x = x_; x < x_ + w_; ++x)
  {
  }

  for (auto y = y_; y < y_ + h_; ++y)
  {
  }
}
