#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <map>
#include <SDL2/SDL.h>

#include "MapSystem.h"

namespace ld
{

static constexpr int TILE_WIDTH = 48;

class RenderSystem
{
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Surface* screen;

  MapSystem& map_system;

  std::map<std::string, SDL_Texture*> textures;

public:
  RenderSystem(SDL_Window* window, SDL_Renderer* renderer, MapSystem& map_system);

  SDL_Texture* load_texture(std::string name);
  void setup_textures();
  void update();
};

}

#endif /* RENDERSYSTEM_H */
