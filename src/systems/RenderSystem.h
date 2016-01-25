#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <map>
#include <SDL2/SDL.h>

#include "EntitySystem.h"
#include "MapSystem.h"
#include "CameraSystem.h"

namespace ld
{

class RenderSystem
{
  SDL_Window* window;
  SDL_Renderer* renderer;

  EntitySystem& entity_system;
  MapSystem& map_system;
  CameraSystem& camera_system;

  std::map<std::string, SDL_Texture*> textures;

  int current_floor;

public:
  RenderSystem(
    SDL_Window* window, SDL_Renderer* renderer,
    EntitySystem& entity_system,
    MapSystem& map_system,
    CameraSystem& camera_system);

  SDL_Texture* load_texture(std::string name);
  void setup_textures();
  void update();

  void shutdown();
};

}

#endif /* RENDERSYSTEM_H */
