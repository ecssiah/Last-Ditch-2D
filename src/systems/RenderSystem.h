#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <eigen3/Eigen/Geometry>
#include <map>
#include <SDL2/SDL.h>

#include "../DebugDraw.h"
#include "../SDL_Interface.h"
#include "MapSystem.h"
#include "EntitySystem.h"
#include "CameraSystem.h"
#include "InterfaceSystem.h"
#include "PhysicsSystem.h"

namespace ld
{

class RenderSystem
{
  void setup_textures();
  SDL_Texture* load_texture(std::string name);

  void render();
  void render_chunks(int floor);
  void render_tiles(int floor);
  void render_items(int floor);
  void render_users(int floor);

  void render_tile(Tile& tile);
  void render_items(Chunk& chunk);

  SDL_Interface& sdl_interface;
  DebugDraw debug_draw;

  MapSystem& map_system;
  EntitySystem& entity_system;
  CameraSystem& camera_system;
  InterfaceSystem& interface_system;
  PhysicsSystem& physics_system;

  std::map<std::string, SDL_Texture*> textures;
  std::map<std::string, Eigen::Vector2i> texture_coords;
  std::map<std::string, std::string> type_to_texture_map;

  bool debug;

  User* active_user;

public:
  RenderSystem(
    SDL_Interface& sdl_interface,
    MapSystem& map_system,
    EntitySystem& entity_system,
    CameraSystem& camera_system,
    InterfaceSystem& interface_system,
    PhysicsSystem& physics_system);

  void update();
};

}

#endif /* RENDERSYSTEM_H */
