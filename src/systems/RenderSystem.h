#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <eigen3/Eigen/Geometry>
#include <SDL2/SDL.h>
#include <unordered_map>

#include "../DebugDraw.h"
#include "../SDL_Interface.h"
#include "CameraSystem.h"
#include "EntitySystem.h"
#include "MapSystem.h"
#include "PhysicsSystem.h"
#include "ui/UISystem.h"

namespace ld
{

class RenderSystem
{
  void update_textures();
  void update_animations(const double& dt);

  void render();
  void render_chunks(int floor);
  void render_tiles(int floor);
  void render_items(int floor);
  void render_doors(int floor);
  void render_users(int floor);

  bool debug;

  DebugDraw debug_draw;
  SDL_Interface& sdl_interface;

  MapSystem& map_system;
  EntitySystem& entity_system;
  CameraSystem& camera_system;
  UISystem& ui_system;
  PhysicsSystem& physics_system;

public:
  RenderSystem(
    SDL_Interface& sdl_interface,
    MapSystem& map_system,
    EntitySystem& entity_system,
    CameraSystem& camera_system,
    UISystem& ui_system,
    PhysicsSystem& physics_system);

  void update(const double& dt);
};

}

#endif /* RENDERSYSTEM_H */
