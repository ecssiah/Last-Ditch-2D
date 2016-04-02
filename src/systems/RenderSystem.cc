#include "RenderSystem.h"
#include <iostream>
#include <eigen3/Eigen/Geometry>
#include <SDL2/SDL_image.h>

#include "../Utils.h"
#include "../constants/ItemConstants.h"
#include "../constants/MapConstants.h"
#include "../constants/RenderConstants.h"
#include "../constants/UserConstants.h"

using namespace ld;
using namespace Eigen;
using namespace std;
using namespace Utils;

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
    active_user(_entity_system.get_active_user()),
    debug_draw(_sdl_interface.renderer, _camera_system),
    textures()
{
  physics_system.set_debug_draw(debug_draw);

  setup_textures();

  cout << "RenderSystem ready" << endl;
}


SDL_Texture* RenderSystem::load_texture(std::string name)
{
  auto path("media/textures/" + name + ".png");

  return IMG_LoadTexture(sdl_interface.renderer, path.c_str());
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
  for (auto& user : entity_system.get_users(active_user->floor))
  {
    user.frame_time += dt;

    if (user.frame_time >= user.frame_length)
    {
      user.frame_time = 0.f;

      auto& anim_data(User_Data[user.type].animations[user.animation]);

      if (user.frame < anim_data.frames - 1)
	++user.frame;
      else
	user.frame = 0;

      user.clip_rect.x = anim_data.clip_rect.x + PIXELS_PER_UNIT * user.frame;
      user.clip_rect.y = anim_data.clip_rect.y;
    }

    user.arm_frame_time += dt;

    if (user.arm_frame_time >= user.arm_frame_length)
    {
      user.arm_frame_time = 0.f;

      auto& arm_anim_data(User_Data[user.type].animations[user.arm_animation]);

      if (user.arm_frame < arm_anim_data.frames - 1)
	++user.arm_frame;
      else
	user.arm_frame = 0;

      user.arm_clip_rect.x = anim_data.clip_rect.x + PIXELS_PER_UNIT * user.arm_frame;
      user.arm_clip_rect.y = anim_data.clip_rect.y;
    }
  }
}


void RenderSystem::update_textures()
{

}


void RenderSystem::render()
{
  auto floor(active_user->floor);

  render_chunks(floor);
  render_tiles(floor);
  render_items(floor);
  render_doors(floor);
  render_users(floor);
}


void RenderSystem::render_chunks(int floor)
{
  for (int x(0); x < MAP_SIZE_X; x += TILES_PER_CHUNK_X)
  {
    for (int y(0); y < MAP_SIZE_Y; y += TILES_PER_CHUNK_Y)
      sdl_interface.render_chunk(map_system.get_chunk(x, y, floor));
  }
}


void RenderSystem::render_tiles(int floor)
{
  for (auto cx(0); cx < NUM_CHUNKS_X; ++cx)
  {
    for (auto cy(0); cy < NUM_CHUNKS_Y; ++cy)
    {
      auto& chunk(
	map_system.get_chunk(TILES_PER_CHUNK_X * cx, TILES_PER_CHUNK_Y * cy, floor));

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
      auto& chunk(map_system.get_chunk(TILES_PER_CHUNK_X * x, TILES_PER_CHUNK_Y * y, floor));

      for (auto& item : chunk.items)
	if (!item.contained) render_item(item);
    }
  }
}


void RenderSystem::render_doors(int floor)
{
  for (auto cx(0); cx < NUM_CHUNKS_X; ++cx)
  {
    for (auto cy(0); cy < NUM_CHUNKS_Y; ++cy)
    {
      auto& chunk(
	map_system.get_chunk(TILES_PER_CHUNK_X * cx, TILES_PER_CHUNK_Y * cy, floor));

      for (auto& door : chunk.doors)
	sdl_interface.render_door(door);
    }
  }
}


void RenderSystem::render_users(int floor)
{
  for (auto& user : entity_system.get_users(floor))
    sdl_interface.render_user(user);
}
