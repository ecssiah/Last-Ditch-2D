#include "RenderSystem.h"
#include <iostream>
#include <eigen3/Eigen/Geometry>
#include <SDL2/SDL_image.h>

#include "../StrUtil.h"
#include "../constants/MapConstants.h"
#include "../constants/RenderConstants.h"
#include "../constants/UserConstants.h"

using namespace ld;
using namespace Eigen;
using namespace std;
using namespace StrUtil;

RenderSystem::RenderSystem(
  SDL_Interface& _sdl_interface,
  MapSystem& _map_system,
  EntitySystem& _entity_system,
  CameraSystem& _camera_system,
  InterfaceSystem& _interface_system,
  PhysicsSystem& _physics_system
)
  : debug(false),
    sdl_interface(_sdl_interface),
    map_system(_map_system),
    entity_system(_entity_system),
    camera_system(_camera_system),
    interface_system(_interface_system),
    physics_system(_physics_system),
    active_user(_entity_system.get_active_user()),
    debug_draw(_sdl_interface.renderer, _camera_system),
    textures()
{
  setup_textures();

  physics_system.set_debug_draw(debug_draw);

  cout << "RenderSystem ready" << endl;
}


void RenderSystem::setup_textures()
{
  textures["kadijah"] = load_texture("kadijah");
  textures["chunk_floor1"] = load_texture("chunk_floor1");
  textures["tileset1"] = load_texture("tileset1");
  textures["items1"] = load_texture("items1");
}


SDL_Texture* RenderSystem::load_texture(std::string name)
{
  auto path("media/textures/" + name + ".png");

  return IMG_LoadTexture(sdl_interface.renderer, path.c_str());
}


void RenderSystem::update(const double& dt)
{
  update_animations(dt);

  SDL_SetRenderDrawColor(sdl_interface.renderer, 0, 0, 0, 0);
  SDL_RenderClear(sdl_interface.renderer);

  render();

  interface_system.render();

  if (debug) physics_system.render_debug();

  SDL_RenderPresent(sdl_interface.renderer);
}


void RenderSystem::update_animations(const double& dt)
{
  for (auto& user : entity_system.get_users(active_user->floor))
  {
    user.frame_time += dt;

    if (user.frame_time >= user.frame_length)
    {
      user.frame_time = 0.f;

      const auto& anim_data(USER_ANIMATION_DATA[user.type][user.animation]);

      if (user.frame < anim_data.frames - 1)
	++user.frame;
      else
	user.frame = 0;

      auto x(anim_data.x + PIXELS_PER_UNIT * user.frame);
      auto y(anim_data.y);

      user.clip_rect.x = x;
      user.clip_rect.y = y;
    }

    user.arm_frame_time += dt;

    if (user.arm_frame_time >= user.arm_frame_length)
    {
      user.arm_frame_time = 0.f;

      const auto& arm_anim_data(USER_ANIMATION_DATA[user.type][user.arm_animation]);

      if (user.arm_frame < arm_anim_data.frames - 1)
	++user.arm_frame;
      else
	user.arm_frame = 0;

      auto arm_x(arm_anim_data.x + PIXELS_PER_UNIT * user.arm_frame);
      auto arm_y(arm_anim_data.y);

      user.arm_clip_rect.x = arm_x;
      user.arm_clip_rect.y = arm_y;
    }
  }
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
    {
      auto& chunk(map_system.get_chunk(x, y, floor));

      SDL_Rect dest_rect;
      dest_rect.x =
	PIXELS_PER_UNIT * (chunk.pos.x() - camera_system.get_pos().x()) + HALF_SCREEN_SIZE_X;
      dest_rect.y =
	PIXELS_PER_UNIT * (chunk.pos.y() - camera_system.get_pos().y()) + HALF_SCREEN_SIZE_Y;
      dest_rect.w = PIXELS_PER_UNIT * TILES_PER_CHUNK_X;
      dest_rect.h = PIXELS_PER_UNIT * TILES_PER_CHUNK_Y;

      SDL_RenderCopy(
	sdl_interface.renderer,
	textures[chunk.texture],
	nullptr, &dest_rect);
    }
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
	  render_tile(chunk.floor_tiles[x][y]);

      for (auto x(0); x < TILES_PER_CHUNK_X; ++x)
	for (auto y(0); y < TILES_PER_CHUNK_Y; ++y)
	  render_tile(chunk.main_tiles[x][y]);
    }
  }
}


void RenderSystem::render_tile(Tile& tile)
{
  auto clip_data(MAP_CLIP_DATA[tile.type]);

  SDL_Rect clip_rect;
  clip_rect.x = clip_data.x;
  clip_rect.y = clip_data.y;
  clip_rect.w = clip_data.w;
  clip_rect.h = clip_data.h;

  SDL_Rect dest_rect;
  dest_rect.x =
    PIXELS_PER_UNIT * (tile.pos.x() - camera_system.get_pos().x()) + HALF_SCREEN_SIZE_X;
  dest_rect.y =
    PIXELS_PER_UNIT * (tile.pos.y() - camera_system.get_pos().y()) + HALF_SCREEN_SIZE_Y;
  dest_rect.w = PIXELS_PER_UNIT;
  dest_rect.h = PIXELS_PER_UNIT;

  SDL_RenderCopyEx(
    sdl_interface.renderer,
    textures[tile.texture],
    &clip_rect, &dest_rect,
    tile.rotation,
    nullptr,
    SDL_FLIP_NONE);
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


void RenderSystem::render_item(Item& item)
{
  auto clip_data(MAP_CLIP_DATA[item.type]);

  SDL_Rect clip_rect;
  clip_rect.x = clip_data.x;
  clip_rect.y = clip_data.y;
  clip_rect.w = clip_data.w;
  clip_rect.h = clip_data.h;

  SDL_Rect dest_rect;
  dest_rect.x =
    PIXELS_PER_UNIT * (item.pos.x() - camera_system.get_pos().x()) + HALF_SCREEN_SIZE_X;
  dest_rect.y =
    PIXELS_PER_UNIT * (item.pos.y() - camera_system.get_pos().y()) + HALF_SCREEN_SIZE_Y;
  dest_rect.w = PIXELS_PER_UNIT / 2;
  dest_rect.h = PIXELS_PER_UNIT / 2;

  SDL_RenderCopy(
    sdl_interface.renderer,
    textures[item.texture],
    &clip_rect, &dest_rect);
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
	render_door(door);
    }
  }
}


void RenderSystem::render_door(Door& door)
{
  auto full_type(door.open ? door.type + "_open" : door.type + "_closed");
  auto clip_data(MAP_CLIP_DATA[full_type]);

  SDL_Rect clip_rect;
  clip_rect.x = clip_data.x;
  clip_rect.y = clip_data.y;
  clip_rect.w = clip_data.w;
  clip_rect.h = clip_data.h;

  SDL_Rect dest_rect;
  dest_rect.x =
    PIXELS_PER_UNIT * (door.pos.x() - camera_system.get_pos().x()) + HALF_SCREEN_SIZE_X;
  dest_rect.y =
    PIXELS_PER_UNIT * (door.pos.y() - camera_system.get_pos().y()) + HALF_SCREEN_SIZE_Y;
  dest_rect.w = PIXELS_PER_UNIT;
  dest_rect.h = PIXELS_PER_UNIT;

  SDL_RenderCopy(
    sdl_interface.renderer,
    textures[door.texture],
    &clip_rect, &dest_rect);
}


void RenderSystem::render_users(int floor)
{
  for (auto& user : entity_system.get_users(floor))
  {
    SDL_Rect dest_rect;
    dest_rect.x =
      PIXELS_PER_UNIT * (user.pos.x() - camera_system.get_pos().x()) + HALF_SCREEN_SIZE_X;
    dest_rect.y =
      PIXELS_PER_UNIT * (user.pos.y() - camera_system.get_pos().y()) + HALF_SCREEN_SIZE_Y;
    dest_rect.w = PIXELS_PER_UNIT;
    dest_rect.h = PIXELS_PER_UNIT;

    SDL_RendererFlip flip(
      ends_with(user.animation, "left") ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);

    SDL_RenderCopyEx(
      sdl_interface.renderer,
      textures[user.texture],
      &user.clip_rect, &dest_rect,
      0,
      nullptr,
      flip);

    SDL_RendererFlip arm_flip(
      ends_with(user.arm_animation, "left") ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);

    if (user.frame % 2 == 0) ++dest_rect.y;

    SDL_RenderCopyEx(
      sdl_interface.renderer,
      textures[user.arm_texture],
      &user.arm_clip_rect, &dest_rect,
      0,
      nullptr,
      arm_flip);
  }
}
