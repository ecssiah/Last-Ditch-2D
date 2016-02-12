#include "RenderSystem.h"
#include <iostream>
#include <eigen3/Eigen/Geometry>
#include <SDL2/SDL_image.h>

#include "../constants/MapConstants.h"
#include "../constants/RenderConstants.h"

using namespace ld;
using namespace Eigen;
using namespace std;

RenderSystem::RenderSystem(
  SDL_Interface& sdl_interface_,
  MapSystem& map_system_,
  EntitySystem& entity_system_,
  CameraSystem& camera_system_,
  InterfaceSystem& interface_system_,
  PhysicsSystem& physics_system_
)
  : sdl_interface(sdl_interface_),
    map_system(map_system_),
    entity_system(entity_system_),
    camera_system(camera_system_),
    interface_system(interface_system_),
    physics_system(physics_system_),
    debug_draw(sdl_interface.renderer, camera_system_),
    textures(),
    texture_coords(),
    debug(false),
    active_user(entity_system.get_active_user())
{
  setup_textures();

  physics_system.set_debug_draw(debug_draw);

  cout << "Render system ready" << endl;
}


void RenderSystem::setup_textures()
{
  textures["kadijah"] = load_texture("kadijah");
  textures["chunk_floor1"] = load_texture("chunk_floor1");

  textures["tileset1"] = load_texture("tileset1");
  texture_coords["wall1"] = {0, 0};
  texture_coords["door1"] = {0, 1};
  texture_coords["stairs_down1"] = {0, 2};
  texture_coords["stairs_up1"] = {1, 2};
  texture_coords["floor1"] = {0, 3};

  textures["items1"] = load_texture("items1");
  texture_coords["scrub1"] = {0, 0};
  texture_coords["container1"] = {1, 0};
}


SDL_Texture* RenderSystem::load_texture(std::string name)
{
  auto path("media/textures/" + name + ".png");

  return IMG_LoadTexture(sdl_interface.renderer, path.c_str());
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
	textures[chunk.texture_name],
	nullptr, &dest_rect);
    }
  }
}


void RenderSystem::render_entities(Chunk& chunk)
{
  for (auto x(0); x < TILES_PER_CHUNK_X; ++x)
    for (auto y(0); y < TILES_PER_CHUNK_Y; ++y)
      render_entity(chunk.floor_entities[x][y]);

  for (auto x(0); x < TILES_PER_CHUNK_X; ++x)
    for (auto y(0); y < TILES_PER_CHUNK_Y; ++y)
      render_entity(chunk.entities[x][y]);
}


void RenderSystem::render_entity(Entity& entity)
{
  SDL_Rect clip_rect;
  clip_rect.x = PIXELS_PER_UNIT * (texture_coords[entity.type].x());
  clip_rect.y = PIXELS_PER_UNIT * (texture_coords[entity.type].y());
  clip_rect.w = PIXELS_PER_UNIT;
  clip_rect.h = PIXELS_PER_UNIT;

  SDL_Rect dest_rect;
  dest_rect.x =
    PIXELS_PER_UNIT * (entity.pos.x() - camera_system.get_pos().x()) + HALF_SCREEN_SIZE_X;
  dest_rect.y =
    PIXELS_PER_UNIT * (entity.pos.y() - camera_system.get_pos().y()) + HALF_SCREEN_SIZE_Y;
  dest_rect.w = PIXELS_PER_UNIT;
  dest_rect.h = PIXELS_PER_UNIT;

  SDL_RenderCopyEx(
    sdl_interface.renderer,
    textures[entity.texture_name],
    &clip_rect, &dest_rect,
    entity.rotation,
    nullptr,
    SDL_FLIP_NONE);
}


void RenderSystem::render_items(Chunk& chunk)
{
  for (auto& item : chunk.items)
  {
    SDL_Rect clip_rect;
    clip_rect.x = PIXELS_PER_UNIT / 2 * (texture_coords[item.type].x());
    clip_rect.y = PIXELS_PER_UNIT / 2 * (texture_coords[item.type].y());
    clip_rect.w = PIXELS_PER_UNIT / 2;
    clip_rect.h = PIXELS_PER_UNIT / 2;

    SDL_Rect dest_rect;
    dest_rect.x =
      PIXELS_PER_UNIT * (item.pos.x() - camera_system.get_pos().x()) + HALF_SCREEN_SIZE_X;
    dest_rect.y =
      PIXELS_PER_UNIT * (item.pos.y() - camera_system.get_pos().y()) + HALF_SCREEN_SIZE_Y;
    dest_rect.w = PIXELS_PER_UNIT / 2;
    dest_rect.h = PIXELS_PER_UNIT / 2;

    SDL_RenderCopy(
      sdl_interface.renderer,
      textures[item.texture_name],
      &clip_rect, &dest_rect);
  }
}


void RenderSystem::render()
{
  auto floor(active_user->floor);

  render_chunks(floor);
  render_tiles(floor);
  render_items(floor);
  render_users(floor);
}


void RenderSystem::render_tiles(int floor)
{
  for (auto x(0); x < NUM_CHUNKS_X; ++x)
  {
    for (auto y(0); y < NUM_CHUNKS_Y; ++y)
    {
      auto& chunk(map_system.get_chunk(TILES_PER_CHUNK_X * x, TILES_PER_CHUNK_Y * y, floor));

      render_entities(chunk);
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

      render_items(chunk);
    }
  }
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

    SDL_RenderCopy(
      sdl_interface.renderer,
      textures[user.texture_name],
      &user.clip_rect, &dest_rect);
  }
}


void RenderSystem::update()
{
  SDL_SetRenderDrawColor(sdl_interface.renderer, 0, 0, 0, 0);
  SDL_RenderClear(sdl_interface.renderer);

  render();

  interface_system.render();

  if (debug) physics_system.render_debug();

  SDL_RenderPresent(sdl_interface.renderer);
}
