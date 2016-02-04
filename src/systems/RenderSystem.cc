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
    tileset1_coords(),
    items1_coords(),
    current_floor(0)
{
  setup_textures();

  debug_draw.SetFlags(b2Draw::e_shapeBit);

  physics_system.set_debug_draw(debug_draw);

  cout << "Render system ready" << endl;
}


void RenderSystem::setup_textures()
{
  textures["kadijah"] = load_texture("kadijah");
  textures["chunk_floor1"] = load_texture("chunk_floor1");

  textures["tileset1"] = load_texture("tileset1");
  tileset1_coords["wall1"] = {0, 0};
  tileset1_coords["door1"] = {0, 1};
  tileset1_coords["stairs1"] = {0, 2};

  textures["items1"] = load_texture("items1");
  items1_coords["scrub1"] = {0, 0};
  items1_coords["container1"] = {1, 0};
}


SDL_Texture* RenderSystem::load_texture(std::string name)
{
  auto path = "media/textures/" + name + ".png";

  return IMG_LoadTexture(sdl_interface.renderer, path.c_str());
}


void RenderSystem::render_chunks()
{
  for (auto x = 0; x < NUM_CHUNKS_X; ++x)
  {
    for (auto y = 0; y < NUM_CHUNKS_Y; ++y)
    {
      auto& chunk = map_system.get_chunk(x, y, current_floor);

      SDL_Rect dest_rect;
      dest_rect.x =
	TILE_SIZE * (chunk.pos.x() - camera_system.get_pos().x()) + SCREEN_SIZE_X / 2;
      dest_rect.y =
	TILE_SIZE * (chunk.pos.y() - camera_system.get_pos().y()) + SCREEN_SIZE_Y / 2;
      dest_rect.w = TILE_SIZE * TILES_PER_CHUNK_X;
      dest_rect.h = TILE_SIZE * TILES_PER_CHUNK_Y;

      SDL_RenderCopy(sdl_interface.renderer, textures[chunk.type], nullptr, &dest_rect);

      render_tiles(chunk);
    }
  }
}


void RenderSystem::render_tiles(Chunk& chunk)
{
  for (auto x = 0; x < TILES_PER_CHUNK_X; ++x)
  {
    for (auto y = 0; y < TILES_PER_CHUNK_Y; ++y)
    {
      auto& tile = chunk.tiles[x][y];

      SDL_Rect clip_rect;
      clip_rect.x = TILE_SIZE * (tileset1_coords[tile.type].x());
      clip_rect.y = TILE_SIZE * (tileset1_coords[tile.type].y());
      clip_rect.w = TILE_SIZE;
      clip_rect.h = TILE_SIZE;

      SDL_Rect dest_rect;
      dest_rect.x =
	TILE_SIZE * (chunk.pos.x() + x - camera_system.get_pos().x()) + SCREEN_SIZE_X / 2;
      dest_rect.y =
	TILE_SIZE * (chunk.pos.y() + y - camera_system.get_pos().y()) + SCREEN_SIZE_Y / 2;
      dest_rect.w = TILE_SIZE;
      dest_rect.h = TILE_SIZE;

      SDL_RenderCopyEx(
	sdl_interface.renderer,
	textures["tileset1"],
	&clip_rect, &dest_rect,
	tile.rotation,
	nullptr,
	SDL_FLIP_NONE);
    }
  }
}


void RenderSystem::render_items()
{
  for (auto& item : entity_system.get_items())
  {
    SDL_Rect clip_rect;
    clip_rect.x = TILE_SIZE / 2 * (items1_coords[item.type].x());
    clip_rect.y = TILE_SIZE / 2 * (items1_coords[item.type].y());
    clip_rect.w = TILE_SIZE / 2;
    clip_rect.h = TILE_SIZE / 2;

    SDL_Rect dest_rect;
    dest_rect.x =
      TILE_SIZE * (item.pos.x() - camera_system.get_pos().x()) + SCREEN_SIZE_X / 2;
    dest_rect.y =
      TILE_SIZE * (item.pos.y() - camera_system.get_pos().y()) + SCREEN_SIZE_Y / 2;
    dest_rect.w = TILE_SIZE / 2;
    dest_rect.h = TILE_SIZE / 2;

    SDL_RenderCopy(sdl_interface.renderer, textures["items1"], &clip_rect, &dest_rect);
  }
}


void RenderSystem::render_entities()
{
  for (auto& entity : entity_system.get_dynamic_entities())
  {
    SDL_Rect dest_rect;
    dest_rect.x =
      TILE_SIZE * (entity.pos.x() - camera_system.get_pos().x()) + SCREEN_SIZE_X / 2;
    dest_rect.y =
      TILE_SIZE * (entity.pos.y() - camera_system.get_pos().y()) + SCREEN_SIZE_Y / 2;
    dest_rect.w = TILE_SIZE;
    dest_rect.h = TILE_SIZE;

    SDL_RenderCopy(
      sdl_interface.renderer,
      textures[entity.type],
      &entity.clip_rect, &dest_rect);
  }
}


void RenderSystem::update()
{
  SDL_SetRenderDrawColor(sdl_interface.renderer, 0, 0, 0, 0);

  SDL_RenderClear(sdl_interface.renderer);

  render_chunks();
  render_items();
  render_entities();

  interface_system.render();

  // physics_system.render_debug();

  SDL_RenderPresent(sdl_interface.renderer);
}


void RenderSystem::shutdown()
{
  for (auto& pair : textures)
    SDL_DestroyTexture(pair.second);
}
