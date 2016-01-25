#ifndef MAPCONSTANTS_H
#define MAPCONSTANTS_H

namespace ld
{

constexpr int TILE_SIZE = 48;
constexpr int NUM_CHUNKS_X = 2;
constexpr int NUM_CHUNKS_Y = 2;
constexpr int TILES_PER_CHUNK_X = 20;
constexpr int TILES_PER_CHUNK_Y = 20;
constexpr int MAP_SIZE_X = NUM_CHUNKS_X * TILES_PER_CHUNK_X;
constexpr int MAP_SIZE_Y = NUM_CHUNKS_Y * TILES_PER_CHUNK_Y;
constexpr int NUM_FLOORS = 2;

}

#endif /* MAPCONSTANTS_H */
