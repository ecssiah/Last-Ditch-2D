#ifndef MAPCONSTANTS_H
#define MAPCONSTANTS_H

#include <string>
#include <unordered_map>

#include "../components/info/TileInfo.h"

namespace ld
{

extern const unsigned NUM_CHUNKS_X;
extern const unsigned NUM_CHUNKS_Y;
extern const unsigned TILES_PER_CHUNK_X;
extern const unsigned TILES_PER_CHUNK_Y;
extern const unsigned MAP_SIZE_X;
extern const unsigned MAP_SIZE_Y;
extern const unsigned NUM_FLOORS;

extern std::unordered_map<std::string, TileInfo> Tile_Data;

}

#endif /* MAPCONSTANTS_H */
