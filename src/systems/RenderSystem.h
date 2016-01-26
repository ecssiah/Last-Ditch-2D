#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <eigen3/Eigen/Geometry>
#include <map>
#include <SDL2/SDL.h>

#include "EntitySystem.h"
#include "MapSystem.h"
#include "CameraSystem.h"

namespace ld
{

class RenderSystem
{
  void setup_textures();
  SDL_Texture* load_texture(std::string name);

  void render_chunks();
  void render_tiles(Chunk& chunk);
  void render_entities();

  SDL_Window* window;
  SDL_Renderer* renderer;

  EntitySystem& entity_system;
  MapSystem& map_system;
  CameraSystem& camera_system;

  std::map<std::string, SDL_Texture*> textures;
  std::map<std::string, Eigen::Vector2i> tileset1_coords;

  int current_floor;

public:
  RenderSystem(
    SDL_Window* window, SDL_Renderer* renderer,
    EntitySystem& entity_system,
    MapSystem& map_system,
    CameraSystem& camera_system);

  void update();
  void shutdown();
};

}

#endif /* RENDERSYSTEM_H */
