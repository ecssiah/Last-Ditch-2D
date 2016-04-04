#include "MapConstants.h"

#include "RenderConstants.h"

namespace ld
{

const unsigned NUM_CHUNKS_X(2);
const unsigned NUM_CHUNKS_Y(2);
const unsigned TILES_PER_CHUNK_X(12);
const unsigned TILES_PER_CHUNK_Y(12);
const unsigned MAP_SIZE_X(NUM_CHUNKS_X * TILES_PER_CHUNK_X);
const unsigned MAP_SIZE_Y(NUM_CHUNKS_Y * TILES_PER_CHUNK_Y);
const unsigned NUM_FLOORS(2);

std::unordered_map<std::string, TileInfo> Tile_Data;

}
