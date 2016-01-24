#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <SDL2/SDL.h>

#include "MapSystem.h"

namespace ld
{

static constexpr int TILE_WIDTH = 48;

class RenderSystem
{
  SDL_Window* window;
  SDL_Surface* screen;

  MapSystem& map_system;

public:
  RenderSystem(SDL_Window* window, MapSystem& map_system);

  void update();
};

}

#endif /* RENDERSYSTEM_H */
