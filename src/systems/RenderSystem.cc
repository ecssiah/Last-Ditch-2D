#include "RenderSystem.h"
#include <iostream>
#include <eigen3/Eigen/Geometry>
#include <SDL2/SDL_image.h>

#include "../Utils.h"
#include "../constants/ItemConstants.h"
#include "../constants/MapConstants.h"
#include "../constants/RenderConstants.h"
#include "../constants/UserConstants.h"

using namespace Eigen;
using namespace std;
using namespace Utils;

namespace ld
{

RenderSystem::RenderSystem(
  SDL_Interface& _sdl_interface,
  MapSystem& _map_system,
  EntitySystem& _entity_system,
  CameraSystem& _camera_system,
  UISystem& _ui_system,
  PhysicsSystem& _physics_system
)
  : debug(false),
    sdl_interface(_sdl_interface),
    map_system(_map_system),
    entity_system(_entity_system),
    camera_system(_camera_system),
    ui_system(_ui_system),
    physics_system(_physics_system),
    debug_draw(_sdl_interface.renderer, _camera_system)
{
  physics_system.set_debug_draw(debug_draw);

  cout << "RenderSystem ready" << endl;
}


void RenderSystem::update(const double& dt)
{
  update_animations(dt);
  update_textures();

  sdl_interface.pre_render();

  render();
  ui_system.render();

  if (debug) physics_system.render_debug();

  sdl_interface.post_render();
}


void RenderSystem::update_animations(const double& dt)
{
  auto& user(entity_system.get_user(0));

  user.frame_time += dt;

  if (user.frame_time >= user.frame_length)
  {
    user.frame_time = 0;

    auto& anim_data(User_Data[user.type].animation_data[user.animation]);

    if (user.frame < anim_data.frames - 1)
      ++user.frame;
    else
      user.frame = 0;

    user.clip_rect.x = anim_data.clip_rect.x + PIXELS_PER_UNIT * user.frame;
    user.clip_rect.y = anim_data.clip_rect.y;
  }
}


void RenderSystem::update_textures()
{

}


void RenderSystem::render()
{
  auto floor(entity_system.get_user(0).floor);

  render_chunks(floor);
  render_tiles(floor);
  render_items(floor);
  render_doors(floor);
  render_users(floor);
}


void RenderSystem::render_chunks(int floor)
{
  for (int cx(0); cx < NUM_CHUNKS_X; ++cx)
    for (int cy(0); cy < NUM_CHUNKS_Y; ++cy)
      sdl_interface.render_entity(map_system.get_chunk(cx, cy, floor));
}


void RenderSystem::render_tiles(int floor)
{
  for (auto cx(0); cx < NUM_CHUNKS_X; ++cx)
  {
    for (auto cy(0); cy < NUM_CHUNKS_Y; ++cy)
    {
      auto& chunk(map_system.get_chunk(cx, cy, floor));

      for (auto x(0); x < TILES_PER_CHUNK_X; ++x)
	for (auto y(0); y < TILES_PER_CHUNK_Y; ++y)
	  sdl_interface.render_tile(chunk.floor_tiles[x][y]);

      for (auto x(0); x < TILES_PER_CHUNK_X; ++x)
	for (auto y(0); y < TILES_PER_CHUNK_Y; ++y)
	  sdl_interface.render_tile(chunk.main_tiles[x][y]);
    }
  }
}


void RenderSystem::render_items(int floor)
{
  for (auto x(0); x < NUM_CHUNKS_X; ++x)
  {
    for (auto y(0); y < NUM_CHUNKS_Y; ++y)
    {
      auto& chunk(map_system.get_chunk(x, y, floor));

      for (auto& item : chunk.items) sdl_interface.render_entity(item);
    }
  }
}


void RenderSystem::render_doors(int floor)
{
  for (auto cx(0); cx < NUM_CHUNKS_X; ++cx)
  {
    for (auto cy(0); cy < NUM_CHUNKS_Y; ++cy)
    {
      auto& chunk(map_system.get_chunk(cx, cy, floor));

      for (auto& door : chunk.doors) sdl_interface.render_entity(door);
    }
  }
}


void RenderSystem::render_users(int floor)
{
  sdl_interface.render_user(entity_system.get_user(0));
}

}
